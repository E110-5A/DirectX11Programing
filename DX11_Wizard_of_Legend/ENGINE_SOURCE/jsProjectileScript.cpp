#include "jsProjectileScript.h"
#include "jsObject.h"
#include "jsResources.h"
namespace js
{
	ProjectileScript::ProjectileScript()
		: mTransform(nullptr)
		, mAnimator(nullptr)
		, mAnimationDir(Vector2::Zero)
		, mTesting(false)
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
		TestAnimation();
	}
	void ProjectileScript::Update()
	{
		Testing();
	}
	void ProjectileScript::Render()
	{
	}

	void ProjectileScript::TestAnimation()
	{
		std::shared_ptr<Texture> dragonArc = Resources::Find<Texture>(L"DragonArc");
		mAnimator->Create(L"Test", dragonArc, Vector2(0.0f, 0.0f), Vector2(36.0f, 48.0), Vector2::Zero, 1, 0.1f);
	}

	void ProjectileScript::Testing()
	{
		if (true == mTesting)
		{
			mAnimator->Play(L"Test");
			mTransform->SetPosition(Vector3(1.5f, 1.5f, 1.0f));
		}
	}

	void ProjectileScript::Hit(Script* target)
	{
	}
	void ProjectileScript::WallCollision(Script* target)
	{
	}
}