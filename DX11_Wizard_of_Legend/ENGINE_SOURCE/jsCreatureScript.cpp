#include "jsCreatureScript.h"

// object
#include "jsObject.h"

namespace js
{
	CreatureScript::CreatureScript()
		: mAnimationDir(Vector2(V2RIGHT))
		, mRigidbody(nullptr)
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
		mRigidbody	= GetOwner()->AddComponent<Rigidbody>();
		mAnimator	= GetOwner()->AddComponent<Animator>();
		GetOwner()->AddComponent<Collider2D>();
	}
	void CreatureScript::Update()
	{
	}
	void CreatureScript::Render()
	{
	}
	void CreatureScript::OnCollisionEnter(Collider2D* collider)
	{
		
	}
	void CreatureScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void CreatureScript::OnCollisionExit(Collider2D* collider)
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
		// 상대의 공격 관련 정보를 가져옴
		// 스크립트에서 바로 Tr, Rb 가져올 수 있음
		

		// 자기 자신에게 피해를 줌
	}
	void CreatureScript::WallCollision(Script* target)
	{

	}
	void CreatureScript::FallCollision(Script* target)
	{

	}
}