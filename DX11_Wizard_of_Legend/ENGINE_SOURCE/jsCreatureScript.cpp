#include "jsCreatureScript.h"

#include "jsTime.h"
// object
#include "jsObject.h"

namespace js
{
	CreatureScript::CreatureScript()
		: mAnimationDir(Vector2(V2RIGHT))
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
		mKnockbackCheckTime = 0.4f;
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
		// 조건
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
	void CreatureScript::Hit(ProjectileScript* target)
	{
		TakeDamage(target);
		DoKnockback(target);
	}
	void CreatureScript::TakeDamage(ProjectileScript* target)
	{
		// 채력 깎기
		mHealthStat.curHp -= target->GetProjectileStat().damage;
		// 스테거 적용
		float stagger = target->GetProjectileStat().stagger;
		mHealthStat.curResistance -= stagger;
	}
	void CreatureScript::DoKnockback(ProjectileScript* target)
	{
		// 넉백 저항상태가 아니라면
		if (false == mKnockbacked)
		{
			Vector3 projectilePos = target->GetTransform()->GetPosition();
			Vector3 powerDir = mTransform->GetPosition() - projectilePos;
			float powerDirZ = powerDir.z;
			powerDir.Normalize();
			powerDir.z = powerDirZ;
			Vector3 destPos = mTransform->GetPosition() + powerDir * 0.2f;
			mTransform->SetPosition(destPos);
			mKnockbacked = true;
		}
	}
	void CreatureScript::Blocked(Script* target)
	{

	}
	void CreatureScript::Fall(Script* target)
	{
	}
}