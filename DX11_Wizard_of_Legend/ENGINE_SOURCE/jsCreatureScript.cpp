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
	void CreatureScript::Hit(Script* target)
	{
		TakeDamage(target);
		Knockback(target);
	}
	void CreatureScript::TakeDamage(Script* target)
	{
		// 채력 깎기

		// 스테거 적용
		// Suppressed? subdue?
	}
	void CreatureScript::Knockback(Script* target)
	{
	}
	void CreatureScript::Blocked(Script* target)
	{

	}
	void CreatureScript::Fall(Script* target)
	{
	}
}