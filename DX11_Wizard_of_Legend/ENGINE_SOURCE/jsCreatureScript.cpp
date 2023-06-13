#include "jsCreatureScript.h"

#include "jsObject.h"
#include "jsRenderer.h"
#include "jsCameraScript.h"
#include "jsENVScript.h"
namespace js
{
	CreatureScript::CreatureScript()
		: mAnimationDirection(Vector2(V2RIGHT))
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mHealthStat{}
		, mOffenceStat{}
		, mStuned(false)
		, mStunTime(0.0f)
		, mStunCurrentTime(0.0f)
		, mKnockbacked(false)
		, mKnockbackCheckTime(0.0f)
		, mKnockbackCheckCurrentTime(0.0f)
	{
	}
	CreatureScript::~CreatureScript()
	{
	}
	void CreatureScript::Initialize()
	{
		mTransform	= GetOwner()->GetComponent<Transform>();
		mAnimator	= GetOwner()->AddComponent<Animator>();
		mCollider	= GetOwner()->AddComponent<Collider2D>();
		mRigidbody	= GetOwner()->AddComponent<Rigidbody>();
		mKnockbackCheckTime = 0.3f;
	}
	void CreatureScript::Update()
	{
		KnocbackResistance();
	}
	void CreatureScript::Render()
	{
	}

	void CreatureScript::initializeHealthStat(float maxHp, float regHp, float moveSpeed, float resistance)
	{
		mHealthStat.maxHp = maxHp;
		mHealthStat.curHp = maxHp;
		mHealthStat.regHp = regHp;
		mHealthStat.moveSpeed = moveSpeed;
		mHealthStat.maxResistance = resistance;
		mHealthStat.curResistance = resistance;
		mHealthStat.standing = true;
	}
	void CreatureScript::initializeOffenceStat(float power, float criticalChance, float criticalDamage)
	{
		mOffenceStat.power = power;
		mOffenceStat.criticalChance = criticalChance;
		mOffenceStat.criticalDamage = criticalDamage;
	}
	void CreatureScript::StunStateCheck()
	{
		// ����
		if (0 >= mHealthStat.curResistance)
			mStuned = true;
		
		if (true == mStuned)
		{
			mStunCurrentTime += Time::DeltaTime();
			if (mStunCurrentTime >= mStunTime)
			{
				mStunCurrentTime = 0.0f;
				mStuned = false;
			}
		}
		
	}
	void CreatureScript::KnocbackResistance()
	{
		if (true == mKnockbacked)
		{
			mKnockbackCheckCurrentTime += Time::DeltaTime();
			if (mKnockbackCheckCurrentTime >= mKnockbackCheckTime)
			{
				mKnockbackCheckCurrentTime = 0;
				mKnockbacked = false;
			}
		}
	}
	void CreatureScript::FindTargetType(Collider2D* collider)
	{
		GameObject* object = collider->GetOwner();		

		CollisionOther(object);
	}
	void CreatureScript::CollisionOther(GameObject* target)
	{
		if (nullptr == target)
			return;
		if (eLayerType::Tile == target->GetLayerType())
			CollisionByTile(target);
		if (eLayerType::ENV == target->GetLayerType())
			CollisionByENV(target);
		if (eLayerType::Trap == target->GetLayerType())
			CollisionByTrap(target);
	}


	void CreatureScript::CollisionByTile(GameObject* target)
	{
		if (nullptr == target)
			return;
		eTileCollider type = dynamic_cast<Tile*>(target)->GetTileCollisionType();
		// �̵� ������ ����ó���� �߰��ؾ��� (��ö����, �˹��̶����)
		if (eTileCollider::Wall == type || eTileCollider::FallArea == type)
			Blocked(target);
	}
	void CreatureScript::CollisionByENV(GameObject* target)
	{
		std::vector<Script*> scripts = target->GetScripts();
		Script* colliderScript = dynamic_cast<Script*>(scripts[0]);
		dynamic_cast<ENVScript*>(colliderScript)->DestroyObj();		
	}
	void CreatureScript::CollisionByTrap(GameObject* target)
	{
		std::vector<Script*> scripts = target->GetScripts();
		Script* colliderScript = dynamic_cast<Script*>(scripts[0]);
		Damaged(dynamic_cast<ProjectileScript*>(target));
	}

	void CreatureScript::Damaged(ProjectileScript* target)
	{
		TakeDamage(target);
		Knockback(target);
		std::vector<Script*> camera = renderer::mainCamera->GetOwner()->GetScripts();
		CameraScript* cameraScript = dynamic_cast<CameraScript*>(camera[0]);
		cameraScript->SetOscillation(70.0f, 0.150f);
	}
	void CreatureScript::TakeDamage(ProjectileScript* target)
	{
		// ä�� ���
		mHealthStat.curHp -= target->GetProjectileStat().damage;
		// ���װ� ����
		float stagger = target->GetProjectileStat().stagger;
		mHealthStat.curResistance -= stagger;
	}
	void CreatureScript::Knockback(ProjectileScript* target)
	{
		// �˹� ���׻��°� �ƴ϶��
		if (false == mKnockbacked)
		{
			mKnockbacked = true;
			// ���� ���ϱ�
			Vector3 projectilePos = target->GetTransform()->GetPosition();
			Vector3 powerDir = mTransform->GetPosition() - projectilePos;
			float powerDirZ = powerDir.z;
			powerDir.Normalize();
			powerDir.z = powerDirZ;
			mRigidbody->SetVelocity(Vector2(powerDir.x, powerDir.y) * 30.0f);
		}
	}
	
	void CreatureScript::Blocked(GameObject* target)
	{
		Vector3 tilePos = target->GetComponent<Collider2D>()->GetPosition();
		Vector3 myPos = mCollider->GetPosition();

		// ũ���İ� �浹���� �� ���� ���ϱ�
		Vector3 wallLocationDir = myPos - tilePos;
		Vector2 backwardDir(wallLocationDir.x, wallLocationDir.y);
		// �ش� ���� �ӵ� �����ϱ�
		mRigidbody->EraseVelocity(wallLocationDir, mRigidbody->GetVelocity());

		// �� �κи�ŭ �ٽ� ������ �����
		// ��� �浹ü ��ġ�� �� �浹ü ��ġ ���ϱ�
		Vector2 v2TilePos(tilePos.x, tilePos.y);
		Vector2 v2myPos(myPos.x, myPos.y);

		float distance = Vector2::Distance(v2myPos, v2TilePos);

		// ��� �浹ü ũ��� �� �浹ü ũ�� ���ϱ�
		Vector2 tileSize = target->GetComponent<Collider2D>()->GetSize();
		Vector2 mySize = mCollider->GetSize();
		float tileLength = tileSize.Length();
		float myLength = mySize.Length();
		float collisionLength = tileLength - myLength;
		// �� �浹ü ������ �Ÿ��� �� �浹ü ũ���� �պ��� ������� �� ���̸�ŭ �� ��ġ�� �̵���Ű��
		float difference = distance - collisionLength;
		Vector3 myTrPos = mTransform->GetPosition();
		if (0 <= difference)
		{
			backwardDir.Normalize();
			myTrPos.x += backwardDir.x * difference;
			myTrPos.y += backwardDir.y * difference;
			mTransform->SetPosition(myTrPos);
		}
	}
	void CreatureScript::ExitBlock(Script* target)
	{
	}
	void CreatureScript::Fall(Script* target)
	{
		// �ǵ��ư��� ��� �߰�
	}
}