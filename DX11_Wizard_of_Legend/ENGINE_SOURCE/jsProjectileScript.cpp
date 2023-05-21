#include "jsProjectileScript.h"
#include "jsObject.h"
#include "jsResources.h"
#include "GameObjectsAndScripts.h"
namespace js
{
	ProjectileScript::ProjectileScript()
		: mTransform(nullptr)
		, mAnimator(nullptr)
		, mAnimationDirection(Vector2::Zero)
		, mTesting(false)
		, mProjectileAble(false)
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
		ProjectileProcess();
	}
	void ProjectileScript::Render()
	{
	}

	void ProjectileScript::OnCollisionEnter(Collider2D* collider)
	{
		// 누구인지 확인하기
		eLayerType targetType = collider->GetOwner()->GetLayerType();
		std::vector<Script*> targetScript = collider->GetOwner()->GetScripts();

		if (false == mIsHostile)
		{
			if (eLayerType::MonsterProjectile == targetType)
			{
				ProjectileScript* projectile = dynamic_cast<ProjectileScript*>(targetScript[0]);
				CollisionByProjectile(projectile);
			}
			if (eLayerType::Monster == targetType)
			{
				CreatureScript* creature = dynamic_cast<CreatureScript*>(targetScript[0]);
				CollisionByCreature(creature);
			}
		}
		else
		{
			if (eLayerType::PlayerProjectile == targetType)
			{
				ProjectileScript* projectile = dynamic_cast<ProjectileScript*>(targetScript[0]);
				CollisionByProjectile(projectile);
			}
			if (eLayerType::Player == targetType)
			{
				CreatureScript* creature = dynamic_cast<CreatureScript*>(targetScript[0]);
				CollisionByCreature(creature);
			}
		}
		
		if (eLayerType::Wall == targetType)
		{
			CollisionByWall(targetScript[0]);
		}		
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
	}

	void ProjectileScript::ProjectileProcess()
	{
		if (false == mProjectileAble) 
			GetOwner()->OnPause();
		ProjectileEndCheck();
	}

	void ProjectileScript::ProjectileEndCheck()
	{
		if (0 >= mProjectileStat.damage)
			Disappear();
	}

	void ProjectileScript::CollisionByProjectile(Script* target)
	{
		// 상대방 스텟정보 가져오기
		ProjectileScript* projectile = dynamic_cast<ProjectileScript*>(target);
		// 채력 깎기

		
		// 채력이 없으면 사라지기
		// 조건에 맞다면 폭발하기
		Boom(target);
		Disappear();
	}

	void ProjectileScript::CollisionByCreature(Script* target)
	{
		CreatureScript* creature = dynamic_cast<CreatureScript*>(target);
		Hit(target);
		Boom(target);
		Disappear();
	}

	void ProjectileScript::CollisionByWall(Script* target)
	{
		Boom(target);
		Disappear();
	}

	void ProjectileScript::Hit(Script* target)
	{
		// 상대가 투사체라면
		if (eLayerType::PlayerProjectile == target->GetOwner()->GetLayerType()
			|| eLayerType::PlayerProjectile == target->GetOwner()->GetLayerType())
		{
		// 투사체끼리 피해를 주고 받음
			ProjectileScript* projectile = dynamic_cast<ProjectileScript*>(target);
			projectile->Damaged(mProjectileStat.damage);
		}

		// 상대가 오브젝트라면
		if (eLayerType::PlayerProjectile == target->GetOwner()->GetLayerType())
		{
		// 대상에게 피해를 줌
			CreatureScript* creature = dynamic_cast<CreatureScript*>(target);
			creature->Hit(this);
		}
	}
	void ProjectileScript::Disappear()
	{
		mProjectileAble = false;		
	}
	void ProjectileScript::Boom(Script* target)
	{
		// 내가 무엇인지에 따라서 폭발할수도 있습니다..!
	}
	void ProjectileScript::Damaged(float otherProjectile)
	{
	}
}