#include "jsCreatureScript.h"

// component
#include "jsRigidbody.h"
#include "jsTransform.h"

// object
#include "jsGameObject.h"


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
	void CreatureScript::Hit(Script* target)
	{
		// ����� ���� ���� ������ ������
		// �ڱ� �ڽſ��� ���ظ� ��
	}
	void CreatureScript::WallCollision(Script* target)
	{

	}
	void CreatureScript::FallCollision(Script* target)
	{

	}
}