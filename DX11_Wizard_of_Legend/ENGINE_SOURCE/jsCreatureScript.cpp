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
		GetOwner()->AddComponent<Collider2D>();
	}
	void CreatureScript::Update()
	{
	}
	void CreatureScript::Render()
	{
	}


	void CreatureScript::initializeHealthStat(float maxHp, float curHp, float regHp, float moveSpeed)
	{
		mHealthStat.maxHp = maxHp;
		mHealthStat.curHp = curHp;
		mHealthStat.regHp = regHp;
		mHealthStat.moveSpeed = moveSpeed;
	}
	void CreatureScript::initializeOffenceStat(float power, float criticalChance, float criticalDamage)
	{
		mOffenceStat.power = power;
		mOffenceStat.criticalChance = criticalChance;
		mOffenceStat.criticalDamage = criticalDamage;
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
	}
	void CreatureScript::Knockback(ProjectileScript* target)
	{
		// 대상과 내 위치의 간격으로 방향벡터를 구하기
		Vector3 projectilePos = target->GetTransform()->GetPosition();
		Vector3 powerDir = projectilePos - mTransform->GetPosition();
		powerDir.Normalize();

		mTransform->SetPosition(powerDir * 1.1f);
	}
	void CreatureScript::Blocked(Script* target)
	{

	}
	void CreatureScript::Fall(Script* target)
	{
	}
}