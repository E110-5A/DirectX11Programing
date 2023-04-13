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
		: mCategory(eArcanaCategory::Melee)
		, mLifeTime(2.0f)
		, mAddTime(0.0f)
		, mMeleeVelocity(30.0f)
		, mProjectileSpeed(16.0f)
		, mIsReady(true)
	{
	}
	ArcanaScript::~ArcanaScript()
	{
	}
	void ArcanaScript::Initialize()
	{
		CreateAnimation();
	}
	void ArcanaScript::Update()
	{
		if (mAddTime < mLifeTime)
			mAddTime += Time::DeltaTime();
		else
		{
			die();
			return;
		}

		if (eArcanaCategory::Projectile == mCategory)
		{
			Transform* myTr = GetOwner()->GetComponent<Transform>();
			Vector3 pos = myTr->GetPosition();
			pos += myTr->Up() * mProjectileSpeed * Time::DeltaTime();
			myTr->SetPosition(pos);
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
		if (eArcanaCategory::Melee == mCategory)
		{
			myRigidbody->SetVelocity(shootDir * mMeleeVelocity);
		}
		else
		{
			//myRigidbody->SetVelocity(shootDir * 80.0f);
		}
		//Transform* tr = GetOwner()->GetComponent<Transform>();

		//Vector3 pos = tr->GetPosition();
		//pos += tr->Up() * mMoveSpeed * Time::DeltaTime();
		//tr->SetPosition(pos);

	}
	void ArcanaScript::CreateAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		// 府家胶 啊廉客辑 积己
		std::shared_ptr<Texture> windSlash = Resources::Find<Texture>(L"WindSlash");
		std::shared_ptr<Texture> fireArrow = Resources::Find<Texture>(L"FireArrow");

		animator->Create(L"WindSlash", windSlash, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.08f);
		animator->GetCompleteEvent(L"WindSlash") = std::bind(&ArcanaScript::die, this);
		animator->GetActionEvent(L"WindSlash", 2) = std::bind(&ArcanaScript::shoot, this);
		animator->GetStartEvent(L"WindSlash") = std::bind(&ArcanaScript::activated, this);

		animator->Create(L"FireArrow", fireArrow, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.08f);
		animator->GetActionEvent(L"FireArrow", 1) = std::bind(&ArcanaScript::shoot, this);
		animator->GetStartEvent(L"FireArrow") = std::bind(&ArcanaScript::activated, this);
	}

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
	void ArcanaScript::die()
	{
		mAddTime = mLifeTime;
		mIsReady = true;
	}
	void ArcanaScript::shoot()
	{
		move();
	}
	void ArcanaScript::activated()
	{
		mIsReady = false;
	}
	void ArcanaScript::ready()
	{
		mIsReady = true;
	}
}
