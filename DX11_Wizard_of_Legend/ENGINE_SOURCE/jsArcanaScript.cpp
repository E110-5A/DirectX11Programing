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
		, mStartPos(Vector3::Zero)
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
		if (eArcanaState::Disabled == mArcanaState)
			GetOwner()->OnPause();

		// ���� �Լ�
		endConditionProjectile();
		// �۵� �Լ�
		move();
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
#pragma region Initalize
	void ArcanaScript::createAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		// ���ҽ� �����ͼ� ����
		std::shared_ptr<Texture> windSlash = Resources::Find<Texture>(L"WindSlash");
		std::shared_ptr<Texture> fireArrow = Resources::Find<Texture>(L"FireArrow");

		animator->Create(L"WindSlash", windSlash, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.08f);
		animator->Create(L"FireArrow", fireArrow, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.08f);
	}

	void ArcanaScript::addEvents()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// Melee
		animator->GetCompleteEvent(L"WindSlash") = std::bind(&ArcanaScript::endConditionMelee, this);

		// Projectile
	}
#pragma endregion
	
	// �÷��̾�κ��� ȣ�����
	void ArcanaScript::ActiveArcana(ArcanaStat& skillInfo, float power)
	{
		// ���� �ʱ�ȭ
		mArcanaStat = &skillInfo;
		mArcanaState = eArcanaState::Active;
		mStartPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		mPower = power;
		GetOwner()->OnActive();
		// �ִϸ��̼� ����
		bindAnimation();
	}

	void ArcanaScript::move()
	{
		if (nullptr == mArcanaStat)
			return;

		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector2 shootDir(myTr->Up().x, myTr->Up().y);
		// melee
		if (eArcanaCategory::Melee == mArcanaStat->category)
		{
			myRigidbody->SetVelocity(shootDir * mArcanaStat->moveSpeed);
		}

		// projectile
		if (eArcanaCategory::Projectile == mArcanaStat->category)
		{
			Transform* myTr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = myTr->GetPosition();
			pos += myTr->Up() * mArcanaStat->moveSpeed * Time::DeltaTime();
			myTr->SetPosition(pos);
			
		}
	}

	
	

	void ArcanaScript::bindAnimation()
	{
		if (eArcanaType::AA == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash", false);
		}
		else if (eArcanaType::Skill == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"FireArrow");
		}
		else if (eArcanaType::Dash == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash");
		}
		else if (eArcanaType::Special == mArcanaStat->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash");
		}
		else if (eArcanaType::Ultimate == mArcanaStat->arcanaType)
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
		if (nullptr == mArcanaStat)
			return;
		
		if (eArcanaCategory::Projectile == mArcanaStat->category)
		{
			// �����Ÿ� �̵��ϸ� ����
			Vector3 currentPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			
			if (mArcanaStat->spellRange <= Vector3::Distance(mStartPos, currentPos))
			{
				mArcanaState = eArcanaState::Disabled;
			}
		}
	}
}
