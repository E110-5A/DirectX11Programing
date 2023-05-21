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
		// �������� Ȯ���ϱ�
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
		// ���� �������� ��������
		ProjectileScript* projectile = dynamic_cast<ProjectileScript*>(target);
		// ä�� ���

		
		// ä���� ������ �������
		// ���ǿ� �´ٸ� �����ϱ�
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
		// ��밡 ����ü���
		if (eLayerType::PlayerProjectile == target->GetOwner()->GetLayerType()
			|| eLayerType::PlayerProjectile == target->GetOwner()->GetLayerType())
		{
		// ����ü���� ���ظ� �ְ� ����
			ProjectileScript* projectile = dynamic_cast<ProjectileScript*>(target);
			projectile->Damaged(mProjectileStat.damage);
		}

		// ��밡 ������Ʈ���
		if (eLayerType::PlayerProjectile == target->GetOwner()->GetLayerType())
		{
		// ��󿡰� ���ظ� ��
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
		// ���� ���������� ���� �����Ҽ��� �ֽ��ϴ�..!
	}
	void ProjectileScript::Damaged(float otherProjectile)
	{
	}
}