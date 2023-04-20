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
		, mInfo(nullptr)
		, mArcanaState(eArcanaState::Disabled)
		, mStartPos(Vector3::Zero)

		, mCategory(eArcanaCategory::Melee)
		, mLifeTime(2.0f)
		, mAddTime(0.0f)
		, mMeleeVelocity(30.0f)
		, mProjectileSpeed(16.0f)
	{
	}
	ArcanaScript::~ArcanaScript()
	{
	}
	void ArcanaScript::Initialize()
	{
		// �ִϸ��̼� ����
		createAnimation();

		// �̺�Ʈ ����
		addEvents();
	}

	void ArcanaScript::Update()
	{
		if (eArcanaState::Active != mArcanaState)
			return;

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
	void ArcanaScript::ActiveArcana(ArcanaInfo& skillInfo)
	{
		// ���� �ʱ�ȭ
		mInfo = &skillInfo;
		mArcanaState = eArcanaState::Active;
		mStartPos = GetOwner()->GetComponent<Transform>()->GetPosition();

		// �ִϸ��̼� ����
		bindAnimation();
	}

	void ArcanaScript::move()
	{
		if (nullptr == mInfo)
			return;

		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector2 shootDir(myTr->Up().x, myTr->Up().y);
		// melee
		if (eArcanaCategory::Melee == mInfo->spellStat.category)
		{
			myRigidbody->SetVelocity(shootDir * mInfo->spellStat.moveSpeed);
		}

		// projectile
		if (eArcanaCategory::Projectile == mInfo->spellStat.category)
		{
			Transform* myTr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = myTr->GetPosition();
			pos += myTr->Up() * mInfo->spellStat.moveSpeed * Time::DeltaTime();
			myTr->SetPosition(pos);
		}
	}

	
	

	void ArcanaScript::bindAnimation()
	{
		if (eArcanaType::AA == mInfo->spellStat.arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash", false);
		}
		else if (eArcanaType::Skill == mInfo->spellStat.arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"FireArrow");
		}
		else if (eArcanaType::Dash == mInfo->spellStat.arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash");
		}
		else if (eArcanaType::Special == mInfo->spellStat.arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash");
		}
		else if (eArcanaType::Ultimate == mInfo->spellStat.arcanaType)
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
		if (nullptr == mInfo)
			return;
		
		if (eArcanaCategory::Projectile == mInfo->spellStat.category)
		{
			// �����Ÿ� �̵��ϸ� ����
			Vector3 currentPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			
			if (mInfo->spellStat.spellRange <= Vector3::Distance(mStartPos, currentPos))
			{
				mArcanaState = eArcanaState::Disabled;
			}
		}
	}
}
