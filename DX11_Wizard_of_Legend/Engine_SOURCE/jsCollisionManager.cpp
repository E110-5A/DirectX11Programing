#include "jsCollisionManager.h"
#include "jsSceneManager.h"

namespace js
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End];
	std::map<UINT64, bool> CollisionManager::mCollisionMap;
	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)eLayerType::End; ++row)
		{
			for (UINT column = 0; column < (UINT)eLayerType::End; ++column)
			{
				if (mLayerCollisionMatrix[row][column])
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)column);
				}
			}
		}
	}
	void CollisionManager::FixedUpdate()
	{
	}
	void CollisionManager::Render()
	{
	}
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int column = 0;

		if ((UINT)left <= (UINT)right)
		{
			row = (UINT)left;
			column = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			column = (UINT)left;
		}
		mLayerCollisionMatrix[row][column] = enable;
	}
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (GameObject* left : lefts)
		{
			if (GameObject::Active != left->GetState())
				continue;
			if (nullptr == left->GetComponent<Collider2D>())
				continue;
			for (GameObject* right : rights)
			{
				if (GameObject::Active != right->GetState())
					continue;
				if (nullptr == right->GetComponent<Collider2D>())
					continue;
				if (left == right)
					continue;

				ColliderCollision(left->GetComponent<Collider2D>(), right->GetComponent<Collider2D>());
			}
		}
	}
	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// left right 面倒 ID积己
		ColliderID colliderID;
		colliderID.left = left->GetID();
		colliderID.right = right->GetID();

		//面倒ID 扁馆 面倒沥焊 积己
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		if (Intersect(left, right))
		{
			if (false == iter->second)
			{
				if (left->IsTrigger())
					left->OnTriggerEnter(right);
				else
					left->OnCollisionEnter(right);

				if (right->IsTrigger())
					right->OnTriggerEnter(left);
				else
					right->OnCollisionEnter(left);

				iter->second = true;
			}
			else
			{
				if (left->IsTrigger())
					left->OnTriggerStay(right);
				else
					left->OnCollisionStay(right);

				if (right->IsTrigger())
					right->OnTriggerStay(left);
				else
					right->OnCollisionStay(left);
			}
		}
		else
		{
			if (iter->second == true)
			{
				if (left->IsTrigger())
					left->OnTriggerExit(right);
				else
					left->OnCollisionExit(right);

				if (right->IsTrigger())
					right->OnTriggerExit(left);
				else
					right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		int a = 0;
		if (eColliderType::Rect == left->GetType() && eColliderType::Rect == right->GetType())
		{
			RectCollision(left, right);
		}
		else if (eColliderType::Circle == left->GetType() && eColliderType::Circle == right->GetType())
		{
			CircleCollision(left, right);
		}

		return true;
	}
	bool CollisionManager::RectCollision(Collider2D* left, Collider2D* right)
	{
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2

		// 肺拿 规氢
		static const Vector3 arrLocalPos[4] =
		{
			Vector3{-0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, -0.5f, 0.0f}
			,Vector3{-0.5f, -0.5f, 0.0f}
		};

		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Matrix leftMat = leftTr->GetWorldMatrix();
		Matrix rightMat = rightTr->GetWorldMatrix();

		// 盒府绵 氦磐 ( 捧康 氦磐 )
		Vector3 Axis[4] = {};
		Axis[0] = Vector3::Transform(arrLocalPos[1], leftMat);
		Axis[1] = Vector3::Transform(arrLocalPos[3], leftMat);
		Axis[2] = Vector3::Transform(arrLocalPos[1], rightMat);
		Axis[3] = Vector3::Transform(arrLocalPos[3], rightMat);

		Axis[0] -= Vector3::Transform(arrLocalPos[0], leftMat);
		Axis[1] -= Vector3::Transform(arrLocalPos[0], leftMat);
		Axis[2] -= Vector3::Transform(arrLocalPos[0], rightMat);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], rightMat);

		for (size_t i = 0; i < 4; i++)
		{
			Axis[i].z = 0.0f;
		}

		Vector3 vc = left->GetPosition() - right->GetPosition();
		vc.z = 0.0f;

		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];
			vA.Normalize();

			float projDist = 0.0f;
			for (size_t j = 0; j < 4; j++)
			{
				projDist += fabsf(Axis[j].Dot(vA) / 2.0f);
			}

			if (projDist < fabsf(centerDir.Dot(vA)))
			{
				return false;
			}
		}
		return true;
	}
	bool CollisionManager::CircleCollision(Collider2D* left, Collider2D* right)
	{
		// Circle vs Cirlce
		
		// 馆瘤抚 备窍扁
		float totalRadius = (left->GetRadius() / 2) + (right->GetRadius() / 2);

		// 芭府 备窍扁
		float distanceX = left->GetPosition().x - right->GetPosition().x;
		float distanceY = left->GetPosition().y - right->GetPosition().y;
		Vector2 distance = Vector2(distanceX, distanceY);
		float totaldistance = distance.LengthSquared();

		// 芭府啊 馆瘤抚 钦焊促 累芭唱 鞍栏搁 面倒
		if (totaldistance <= totalRadius)
			return true;

		return false;
	}
}