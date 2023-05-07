#include "jsMonsterScript.h"

#include "jsAnimator.h"
#include "jsRigidbody.h"
#include "jsResources.h"

#include "jsGameObject.h"
#include "jsArcanaScript.h"


namespace js
{
	MonsterScript::MonsterScript()
	{
	}
	MonsterScript::~MonsterScript()
	{
	}

	void MonsterScript::Initialize()
	{
		CreatureScript::Initialize();
		createAnimation();
		initializeHealthStat(20.0f, 20.0f, 0.1f, 2.0f);
		initializeOffenceStat(1.0f, 5.0f, 1.7f);
	}
	void MonsterScript::Update()
	{
		// �ൿ ��ٿ�

		// ���� ����

		// �ൿ ����
	}
	void MonsterScript::Render()
	{
	}

	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{
		// �������� Ȯ���ϱ�
		eLayerType otherType = collider->GetOwner()->GetLayerType();
		std::vector<Script*> otherScript = collider->GetOwner()->GetScripts();

		if (eLayerType::PlayerProjectile == otherType)
		{
			Hit(otherScript[0]);
		}
		if (eLayerType::Wall == otherType)
		{
			CreatureScript::WallCollision(otherScript[0]);
		}
		if (eLayerType::Fall == otherType)
		{
			CreatureScript::FallCollision(otherScript[0]);
		}
	}
	void MonsterScript::Hit(Script* target)
	{
		ArcanaScript* projectile = dynamic_cast<ArcanaScript*>(target);
		// ����� ���� ���� ������ ������
		//float totalDamage = projectile->GetTotalDamage();

		Vector3 myPosition = mTransform->GetPosition();

		Vector3 targetPosition = projectile->GetTransform()->GetPosition();
		Vector3 dir = myPosition - targetPosition ;
		dir.Normalize();

		// �ڱ� �ڽſ��� ���ظ� ��
		//mMonsterStat.curHp -= totalDamage;

		// ���� ���ϱ�

		// �˹��ϱ�
		knockback(dir);
	}
	void MonsterScript::knockback(Vector3 dir)
	{
		Vector2 totalDir = Vector2(dir.x, dir.y);


		Vector2 knockBack = mRigidbody->GetVelocity();
		// ���� * ����
		knockBack = totalDir * 100;
		mRigidbody->AddForce(knockBack);
	}
	void MonsterScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void MonsterScript::createAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Vector2 defaultSize = Vector2(56.0f, 72.0f);
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"GhoulLargeSpriteSheet", L"Monster\\GhoulLargeSprite.png");
		// Idle
		{
			animator->Create(L"GhoulLargeIdleRight", texture, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"GhoulLargeIdleLeft", texture, Vector2(56.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);

			animator->Play(L"GhoulLargeIdleRight");
		}
	}

}