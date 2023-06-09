#include "jsProjectileScript.h"
#include "jsResources.h"
#include "jsObject.h"
#include "jsENVScript.h"
#include "jsInput.h"
namespace js
{
	ProjectileScript::ProjectileScript()
		: mTransform(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
		, mAnimationDirection(Vector2::Zero)
		, mProjectileStat{}
		, mProjectileAbled(false)
		, mFriendly(false)
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
		mCollider = GetOwner()->AddComponent<Collider2D>();
		TestAnimation();
	}
	void ProjectileScript::Update()
	{
		Testing();
	}
	void ProjectileScript::Render()
	{
	}

	void ProjectileScript::OnCollisionEnter(Collider2D* collider)
	{
		FindTargetType(collider);		
	}

	void ProjectileScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void ProjectileScript::OnCollisionExit(Collider2D* collider)
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
		}
		if (Input::GetKeyDown(eKeyCode::Y) && true == mTesting)
		{
			mProjectileStat.damage = 160.0f;
		}
	}

	void ProjectileScript::FindTargetType(Collider2D* collider)
	{
		std::vector<Script*> scripts = collider->GetOwner()->GetScripts();
		Script* colliderScript = dynamic_cast<Script*>(scripts[0]);

		CollisionOther(colliderScript);
	}

	void ProjectileScript::CollisionOther(Script* target)
	{
		if (eLayerType::PlayerProjectile == target->GetOwner()->GetLayerType()
			|| eLayerType::MonsterProjectile == target->GetOwner()->GetLayerType())
			CollisionByProjectile(target);

		if (eLayerType::Player == target->GetOwner()->GetLayerType()
			|| eLayerType::Monster == target->GetOwner()->GetLayerType())
			CollisionByCreature(target);

		if (eLayerType::Wall == target->GetOwner()->GetLayerType())
			CollisionByWall(target);

		if (eLayerType::ENV == target->GetOwner()->GetLayerType())
			CollisionByENV(target);
	}

	void ProjectileScript::CollisionByProjectile(Script* target)
	{
		// 대상의 공격력 값을 가져옴
		ProjectileScript* targetScript = dynamic_cast<ProjectileScript*>(target);
		ProjectileStat targetStat = targetScript->GetProjectileStat();

		ProjectileDamaged(targetStat.damage);
		targetScript->ProjectileDamaged(mProjectileStat.damage);

		if (0 >= mProjectileStat.damage)
			Disappear();
		if (0 >= targetStat.damage)
			targetScript->Disappear();
	}

	void ProjectileScript::CollisionByCreature(Script* target)
	{
		// 대상에게 공격 호출시키기
		CreatureScript* creature = dynamic_cast<CreatureScript*>(target);

		// 피격 함수명 적절하게 변경해주기
		creature->Damaged(this);
	}

	void ProjectileScript::CollisionByWall(Script* target)
	{
		// 사라지기
		Disappear();
	}

	void ProjectileScript::CollisionByENV(Script* target)
	{
		ENVScript* envScript = dynamic_cast<ENVScript*>(target);
		envScript->DestroyObj();
		Disappear();
	}	

	void ProjectileScript::ProjectileDamaged(float otherProjectile)
	{
		mProjectileStat.damage -= otherProjectile;
	}

	void ProjectileScript::Disappear()
	{
		mProjectileAbled = false;
	}
}