#include "jsCreatureScript.h"

// component
#include "jsRigidbody.h"
#include "jsTransform.h"

// object
#include "jsObject.h"


namespace js
{
	CreatureScript::CreatureScript()
		:mAnimationDir(Vector2(V2RIGHT))
	{
	}
	CreatureScript::~CreatureScript()
	{
	}
	void CreatureScript::Initialize()
	{
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();
		mTransform = GetOwner()->GetComponent<Transform>();
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
		// ����� ���� ���� ������ ������
		// ��ũ��Ʈ���� �ٷ� Tr, Rb ������ �� ����
		

		// �ڱ� �ڽſ��� ���ظ� ��
	}
	void CreatureScript::WallCollision(Script* target)
	{

	}
	void CreatureScript::FallCollision(Script* target)
	{

	}
}