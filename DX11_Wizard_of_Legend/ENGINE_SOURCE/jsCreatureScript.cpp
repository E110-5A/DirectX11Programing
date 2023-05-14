#include "jsCreatureScript.h"

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
	}
	void CreatureScript::Update()
	{
		if (0 >= mHealthStat.curResistance)
		{

		}
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
	bool CreatureScript::StunStateCheck()
	{
		if (0 >= mHealthStat.curResistance)
			return true;
		else
			return false;
	}
	void CreatureScript::Hit(ProjectileScript* target)
	{
		TakeDamage(target);
		Knockback(target);
	}
	void CreatureScript::TakeDamage(ProjectileScript* target)
	{
		// 채력 깎기

		// 스테거 적용
		float stagger = target->GetProjectileStat().stagger;
		mHealthStat.curResistance -= stagger;
	}
	void CreatureScript::Knockback(ProjectileScript* target)
	{
		// 넉백 저항상태가 아니라면

		// 대상과 내 위치의 간격으로 방향벡터를 구하기
		Vector3 projectilePos = target->GetTransform()->GetPosition();
		Vector3 powerDir = mTransform->GetPosition() - projectilePos;
		float powerDirZ = powerDir.z;
		powerDir.Normalize();
		powerDir.z = powerDirZ;
		Vector3 destPos = mTransform->GetPosition() + powerDir * 0.2f;

		mTransform->SetPosition(destPos);
	}
	void CreatureScript::Blocked(Script* target)
	{

	}
	void CreatureScript::Fall(Script* target)
	{
	}
}