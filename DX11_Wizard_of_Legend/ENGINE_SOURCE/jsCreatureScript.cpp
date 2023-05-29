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
		mKnockbackCheckTime = 0.15f;
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
		std::vector<Script*> scripts = collider->GetOwner()->GetScripts();
		Script* colliderScript = dynamic_cast<Script*>(scripts[0]);

		CollisionOther(colliderScript);
	}
	void CreatureScript::CollisionOther(Script* target)
	{

		if (eLayerType::Wall == target->GetOwner()->GetLayerType())
			CollisionByWall(target);
		if (eLayerType::ENV == target->GetOwner()->GetLayerType())
			CollisionByENV(target);
		if (eLayerType::Trap == target->GetOwner()->GetLayerType())
			CollisionByTrap(target);
	}


	void CreatureScript::CollisionByWall(Script* target)
	{
		Blocked(target);
	}
	void CreatureScript::CollisionByENV(Script* target)
	{
		ENVScript* envScript = dynamic_cast<ENVScript*>(target);
		envScript->DestroyObj();
	}
	void CreatureScript::CollisionByTrap(Script* target)
	{
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
			mRigidbody->AddForce(Vector2(powerDir.x, powerDir.y) * 70.0f);
		}
	}
	
	void CreatureScript::Blocked(Script* target)
	{
		// ��� ������ �ܺο��� ġ�� ������
		if (eLayerType::Wall == target->GetOwner()->GetLayerType()
			|| eLayerType::FallArea == target->GetOwner()->GetLayerType())
		{
			// �÷��̾��� ������ ������ Ȯ���ϰ�, ���� �浹���̸� �̵��� ���߰�?�ϱ�? �߸𸣰ڳ�
			// rigidbody��Ӹ� �����Ҹ����ĵ� �Ƹ� �ٸ��� �����ؾ��ҵ�
		}
	}
	void CreatureScript::Fall(Script* target)
	{
		// �ǵ��ư��� ��� �߰�
	}
}