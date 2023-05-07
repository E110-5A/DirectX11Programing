#pragma once
#include "jsArcanaScript.h"
#include "jsGameObject.h"
#include "jsTime.h"
#include "jsAnimator.h"
#include "jsResources.h"
#include "jsRigidbody.h"

namespace js
{
	ArcanaScript::ArcanaScript()
		: mSpellID(-1)
		, mArcanaState(eArcanaState::Disabled)
		, mPower(0.0f)
	{	
	}
	ArcanaScript::~ArcanaScript()
	{
	}
	void ArcanaScript::Initialize()
	{
		ProjectileScript::Initialize();
		// �ִϸ��̼� ����
		createAnimation();

		// �̺�Ʈ ����
		addEvents();
	}

	void ArcanaScript::Update()
	{
		// ��Ȱ���� ������Ʈ::��������
		if (eArcanaState::Disabled == mArcanaState)
			GetOwner()->OnPause();

		projectileProcess();

		//// ��Ȱ�� ���� üũ
		//endConditionProjectile();
		//// �۵� �Լ�
		//move();
	}
	void ArcanaScript::FixedUpdate()
	{
	}
	void ArcanaScript::Render()
	{
	}

#pragma region Collision
	void ArcanaScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void ArcanaScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ArcanaScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ArcanaScript::OnTriggerEnter(Collider2D* collider)
	{
	}
	void ArcanaScript::OnTriggerStay(Collider2D* collider)
	{
	}
	void ArcanaScript::OnTriggerExit(Collider2D* collider)
	{
	}
#pragma endregion
#pragma region Events
	void ArcanaScript::Start()
	{

	}
	void ArcanaScript::Complete()
	{
	}
	void ArcanaScript::End()
	{
	}
	void ArcanaScript::Action()
	{
	}
	
#pragma endregion

	void ArcanaScript::ActiveArcana(Arcana* arcana, bool isRight)
	{
		mArcana = arcana;
		mArcanaState = eArcanaState::Active;
		mIsRight = isRight;
		GetOwner()->OnActive();
		playAnimation();
	}

	void ArcanaScript::playAnimation()
	{
		if (eArcanaName::WindSlash == mArcana->arcanaInfo->name)
		{
			mAnimator->Play(L"WindSlash", false);
		}
		else if (eArcanaName::DragonArc == mArcana->arcanaInfo->name)
		{
			if (mIsRight)
				mAnimator->Play(L"DragonArcRight");
			else
				mAnimator->Play(L"DragonArcLeft");
		}
	}

	void ArcanaScript::projectileProcess()
	{
		projectileEndCheck();
		projectileMove();
	}

	void ArcanaScript::projectileEndCheck()
	{
		// Melee Ÿ���� ���, �ִϸ��̼� ����� ������ ���ǿ� �ش���
		// Range Ÿ���� ���, ��Ÿ��� ����� ���ǿ� �ش���
		endConditionProjectile();

		// Disable ���¶��
		if (eArcanaState::Disabled == mArcanaState)
		{
			projectileSleep();
		}

	}

	void ArcanaScript::projectileMove()
	{
		if (eArcanaName::WindSlash == mArcana->arcanaInfo->name)
		{
			Vector2 myDir(mTransform->Up().x, mTransform->Up().y);
			mRigidbody->SetVelocity(myDir * mArcana->arcanaStat->moveSpeed);
		}
		else if (eArcanaName::DragonArc == mArcana->arcanaInfo->name)
		{
			Vector3 pos = mTransform->GetPosition(); 
			pos += mTransform->Up() * mArcana->arcanaStat->moveSpeed * Time::DeltaTime();
			mTransform->SetPosition(pos);
			// cos ���� ��� �߰��ϱ�
		}
	}

	void ArcanaScript::projectileSleep()
	{
		// ��Ȱ�� ����
		mArcanaState = eArcanaState::Disabled;
		// ��ġ �ʱ�ȭ
		mTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	}

	void ArcanaScript::disableProjectile()
	{		
		GetOwner()->OnPause();
	}

#pragma region Initalize
	void ArcanaScript::createAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		// ���ҽ� �����ͼ� ����
		std::shared_ptr<Texture> windSlash = Resources::Find<Texture>(L"WindSlash");
		std::shared_ptr<Texture> fireArrow = Resources::Find<Texture>(L"FireArrow");
		std::shared_ptr<Texture> dragonArc = Resources::Find<Texture>(L"DragonArc");
		//DragonArc.png
		animator->Create(L"WindSlash", windSlash, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.08f);
		animator->Create(L"FireArrow", fireArrow, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.08f);
		animator->Create(L"DragonArcRight", dragonArc, Vector2(0.0f, 0.0f), Vector2(36.0f, 48.0), Vector2::Zero, 1, 0.1f);
		animator->Create(L"DragonArcLeft", dragonArc, Vector2(36.0f, 0.0f), Vector2(36.0f, 48.0), Vector2::Zero, 1, 0.1f);
	}

	void ArcanaScript::addEvents()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// Melee
		animator->GetCompleteEvent(L"WindSlash") = std::bind(&ArcanaScript::endConditionMelee, this);

		// Projectile
	}
#pragma endregion
	
	void ArcanaScript::lActiveArcana(lArcanaStat& skillInfo, float power)
	{
		// ���� �ʱ�ȭ
		mArcanaStat = &skillInfo;
		mArcanaState = eArcanaState::Active;
		mPower = power;
		GetOwner()->OnActive();
		// �ִϸ��̼� ����
		lbindAnimation();
	}
	void ArcanaScript::lmove()
	{
		if (nullptr == mArcanaStat)
			return;

		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector2 shootDir(myTr->Up().x, myTr->Up().y);
		// melee
		if (elArcanaCategory::Melee == mArcanaStat->category)
		{
			myRigidbody->SetVelocity(shootDir * mArcanaStat->moveSpeed);
		}

		// projectile
		if (elArcanaCategory::Projectile == mArcanaStat->category)
		{
			Transform* myTr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = myTr->GetPosition();
			pos += myTr->Up() * mArcanaStat->moveSpeed * Time::DeltaTime();
			myTr->SetPosition(pos);
			
		}
	}
	void ArcanaScript::lbindAnimation()
	{
		if (elArcanaType::AA == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash", false);
		}
		else if (elArcanaType::Skill == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"FireArrow");
		}
		else if (elArcanaType::Dash == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash");
		}
		else if (elArcanaType::Special == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash");
		}
		else if (elArcanaType::Ultimate == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"FireArrow");
		}
	}


	// ���� �Լ�
	void ArcanaScript::endConditionMelee()
	{
		mArcanaState = eArcanaState::Disabled;
	}

	void ArcanaScript::endConditionProjectile()
	{
		if (nullptr == mArcana)
			return;
		
		if (eArcanaCategory::Range == mArcana->arcanaInfo->category)
		{
			// �����Ÿ� �̵��ϸ� ����
			Vector3 currentPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			
			if (mArcana->arcanaStat->spellRange <= Vector3::Distance(Vector3::Zero, currentPos))
			{
				mArcanaState = eArcanaState::Disabled;
			}
		}
	}
}
