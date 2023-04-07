#pragma once
#include "jsArcanaScript.h"
#include "jsGameObject.h"
#include "jsTime.h"
#include "jsAnimator.h"
#include "jsResources.h"

namespace js
{
	ArcanaScript::ArcanaScript()
		: mLifeTime(2.0f)
		, mAddTime(0.0f)
		, mMoveSpeed(0.7f)
	{
	}
	ArcanaScript::~ArcanaScript()
	{
	}
	void ArcanaScript::Initialize()
	{
		createAnimation();
	}
	void ArcanaScript::Update()
	{
		if (mAddTime < mLifeTime)
			mAddTime += Time::DeltaTime();
		else
			return;
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

	void ArcanaScript::move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();
		pos += tr->Up() * mMoveSpeed * Time::DeltaTime();
		tr->SetPosition(pos);
	}

	void ArcanaScript::ActiveProjectile()
	{
		mAddTime = 0;
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->Play(L"WindSlash", false);
	}
	void ArcanaScript::createAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		// 府家胶 啊廉客辑 积己
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"WindSlash");

		animator->Create(L"WindSlash", texture, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 9, 0.1f);
		animator->GetCompleteEvent(L"WindSlash") = std::bind(&ArcanaScript::die, this);


	}
	void ArcanaScript::die()
	{
		mAddTime = mLifeTime;
	}
}
