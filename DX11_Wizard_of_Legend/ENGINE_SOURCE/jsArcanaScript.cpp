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
		: mInfo(nullptr)
		, mCategory(eArcanaCategory::Melee)
		, mLifeTime(2.0f)
		, mAddTime(0.0f)
		, mMeleeVelocity(30.0f)
		, mProjectileSpeed(16.0f)
		, mAvailable(true)
	{
	}
	ArcanaScript::~ArcanaScript()
	{
	}
	void ArcanaScript::Initialize()
	{
		// �ִϸ��̼� ����
		CreateAnimation();

		// �̺�Ʈ ����

	}
	void ArcanaScript::Update()
	{
		// ���� �Լ�

		// �۵� �Լ�


		if (mAddTime < mLifeTime)
			mAddTime += Time::DeltaTime();
		else
		{
			die();
			return;
		}
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

	void ArcanaScript::move()
	{
		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector2 shootDir(myTr->Up().x, myTr->Up().y);
		// melee
		if (eArcanaCategory::Melee == mInfo->category)
		{
			myRigidbody->SetVelocity(shootDir * mMeleeVelocity);
		}

		// projectile
		else if (eArcanaCategory::Projectile == mInfo->category)
		{
			Transform* myTr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = myTr->GetPosition();
			pos += myTr->Up() * mInfo->range * Time::DeltaTime() * 10;
			myTr->SetPosition(pos);
			//myRigidbody->SetVelocity(shootDir * 80.0f);
		}

		// dash = melee



	}
	void ArcanaScript::CreateAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		// ���ҽ� �����ͼ� ����
		std::shared_ptr<Texture> windSlash = Resources::Find<Texture>(L"WindSlash");
		std::shared_ptr<Texture> fireArrow = Resources::Find<Texture>(L"FireArrow");

		animator->Create(L"WindSlash", windSlash, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.08f);
		animator->Create(L"FireArrow", fireArrow, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.08f);
	}

	void ArcanaScript::CreateEvents()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		/*animator->GetCompleteEvent(L"WindSlash") = std::bind(&ArcanaScript::die, this);
		animator->GetActionEvent(L"WindSlash", 2) = std::bind(&ArcanaScript::shoot, this);
		animator->GetStartEvent(L"WindSlash") = std::bind(&ArcanaScript::activated, this);
		animator->GetActionEvent(L"FireArrow", 1) = std::bind(&ArcanaScript::shoot, this);
		animator->GetStartEvent(L"FireArrow") = std::bind(&ArcanaScript::activated, this);*/
	}

	// �Ⱦ�
	void ArcanaScript::ActiveProjectile(eArcanaCategory category)
	{
		mAddTime = 0;
		mCategory = category;

		if (eArcanaCategory::Melee == mCategory)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash", false);
		}
		else if (eArcanaCategory::Projectile == mCategory)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"FireArrow");
		}

	}


	// �÷��̾�κ��� ȣ�����
	void ArcanaScript::ActiveArcana(ArcanaInfo& skillInfo)
	{
		// ��ų ���� ��������
		mInfo = &skillInfo;

		// ��ų Ÿ�Կ� ���� ����� �ִϸ��̼� ���ϱ�
		if (eArcanaType::AA == mInfo->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash", false);
		}
		else if (eArcanaType::Skill == mInfo->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"FireArrow");
		}
		else if (eArcanaType::Dash == mInfo->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash");
		}
		else if (eArcanaType::Special == mInfo->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"WindSlash");
		}
		else if (eArcanaType::Ultimate == mInfo->arcanaType)
		{
			Animator* animator = GetOwner()->GetComponent<Animator>();
			animator->Play(L"FireArrow");
		}
	}


	// ���� �Լ�
	void ArcanaScript::die()
	{
		mAddTime = mLifeTime;
		mAvailable = false;
	}

	// �Ⱦ�
	void ArcanaScript::shoot()
	{
		move();
	}

	// �ܺ� ȣ���
	void ArcanaScript::activated()
	{
		mAvailable = false;
	}
	void ArcanaScript::ready()
	{
		mAvailable = true;
	}
}
