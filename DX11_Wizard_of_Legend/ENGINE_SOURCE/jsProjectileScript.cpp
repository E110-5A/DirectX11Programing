#include "jsProjectileScript.h"
#include "jsObject.h"
namespace js
{
	ProjectileScript::ProjectileScript()
		: mTransform(nullptr)
		, mRigidbody(nullptr)
		, mAnimator(nullptr)
		, mAnimationDir(Vector2::Zero)
	{
	}
	ProjectileScript::~ProjectileScript()
	{
	}
	void ProjectileScript::Initialize()
	{
		mTransform	= GetOwner()->GetComponent<Transform>();
		mRigidbody	= GetOwner()->AddComponent<Rigidbody>();
		mAnimator	= GetOwner()->AddComponent<Animator>();
		GetOwner()->AddComponent<Collider2D>();
	}
	void ProjectileScript::Update()
	{
	}
	void ProjectileScript::Render()
	{
	}
	void ProjectileScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void ProjectileScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ProjectileScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ProjectileScript::Hit(Script* target)
	{
	}
	void ProjectileScript::WallCollision(Script* target)
	{
	}
}