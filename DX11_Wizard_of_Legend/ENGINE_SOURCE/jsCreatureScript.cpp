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
		// 상대의 공격 관련 정보를 가져옴
		// 자기 자신에게 피해를 줌
	}
	void CreatureScript::WallCollision(Script* target)
	{

	}
	void CreatureScript::FallCollision(Script* target)
	{

	}
}