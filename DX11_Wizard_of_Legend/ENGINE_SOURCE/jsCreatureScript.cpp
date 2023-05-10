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
		// ä�� ���

		// ���װ� ����
	}
	void CreatureScript::Knockback(ProjectileScript* target)
	{
		// ���� �� ��ġ�� �������� ���⺤�͸� ���ϱ�
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