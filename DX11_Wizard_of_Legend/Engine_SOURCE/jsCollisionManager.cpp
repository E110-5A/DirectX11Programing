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
		// left right 충돌 ID생성
		ColliderID colliderID;
		colliderID.left = left->GetID();
		colliderID.right = right->GetID();

		//충돌ID 기반 충돌정보 생성
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
		bool ret = true;
		if (eColliderType::Rect == left->GetType() && eColliderType::Rect == right->GetType())
		{
			ret = RectCollision(left, right);
		}
		else if (eColliderType::Circle == left->GetType() && eColliderType::Circle == right->GetType())
		{
			ret = CircleCollision(left, right);
		}

		return ret;
	}
	bool CollisionManager::RectCollision(Collider2D* left, Collider2D* right)
	{
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2

		// 로컬 Rect의 위치값
		static const Vector3 arrLocalPos[4] =
		{
			Vector3{-0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, -0.5f, 0.0f}
			,Vector3{-0.5f, -0.5f, 0.0f}
		};

		// 각각 Tr 가져오기
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		// 각각 World Matrix 가져오기
		Matrix leftMat = leftTr->GetWorldMatrix();
		Matrix rightMat = rightTr->GetWorldMatrix();

		// Scale값 먼저 가져오기 ( 메트릭스에 스케일 값 곱하기 )
		Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);
		Matrix finalLeft = Matrix::CreateScale(leftScale);
		finalLeft *= leftMat;

		Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
		Matrix finalRight = Matrix::CreateScale(rightScale);
		finalRight *= rightMat;

		// 분리축 벡터 만들기 ( 투영 벡터 )

		// 로컬로 생성한 rect 정점에 메트릭스(스케일 적용된)의 회전값을 적용한 벡터를 Axis에 저장

		// Left Right 메트릭스를, 대각선 정점에 곱하여 변환을 준값을 left 0 1, right 2, 3 에 저장한다

		Vector3 Axis[4] = {};
		Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
		Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
		Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
		Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

		// 수직 위치의 정점에 행렬변환한 값을 0,1 2,3 에 빼준다?

		Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

		// Axis.z 값을 0으로 초기화
		for (size_t i = 0; i < 4; i++)
			Axis[i].z = 0.0f;

		// left <-> right 간의 방향을 구한다
		Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
		vc.z = 0.0f;

		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			// 비교할 분리축 벡터 (4개)
			Vector3 vA = Axis[i];
			//vA.Normalize();

			float projDist = 0.0f; // <- 이게 뭔지 모르겠음
			for (size_t j = 0; j < 4; j++)
			{
				projDist += fabsf(Axis[j].Dot(vA) / 2.0f);
				// 내적한 값을 2로 나눠서 계속 더함?
			}

			// 
			if (projDist < fabsf(centerDir.Dot(vA)))
				return false;
		}
		return true;
	}
	bool CollisionManager::CircleCollision(Collider2D* left, Collider2D* right)
	{
		// Circle vs Cirlce
		
		// 스케일 가져오기
		left->GetSize();
		right->GetSize();

		// 반지름 구하기
		float totalRadius = (left->GetRadius() / 2) + (right->GetRadius() / 2);

		// 거리 구하기
		float distanceX = left->GetPosition().x - right->GetPosition().x;
		float distanceY = left->GetPosition().y - right->GetPosition().y;
		Vector2 distance = Vector2(distanceX, distanceY);
		float totaldistance = distance.LengthSquared();

		// 거리가 반지름 합보다 작거나 같으면 충돌
		if (totaldistance <= totalRadius)
			return true;

		return false;
	}
}