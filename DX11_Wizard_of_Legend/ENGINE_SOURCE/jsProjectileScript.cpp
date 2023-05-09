#include "jsProjectileScript.h"
#include "jsObject.h"
namespace js
{
	ProjectileScript::ProjectileScript()
		: mTransform(nullptr)
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
		mAnimator	= GetOwner()->AddComponent<Animator>();
		GetOwner()->AddComponent<Collider2D>();
	}
	void ProjectileScript::Update()
	{
	}
	void ProjectileScript::Render()
	{
	}

	void ProjectileScript::Hit(Script* target)
	{
	}
	void ProjectileScript::WallCollision(Script* target)
	{
	}
}