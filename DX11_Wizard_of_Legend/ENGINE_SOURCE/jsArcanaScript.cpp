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
		, mArcanaState(eProjectileState::Disabled)
		, mArcana(nullptr)
		, mIsRight(true)
		, mStartPos(Vector3(0.0f, 0.0f, 0.0f))
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
		projectileProcess();
	}
	void ArcanaScript::FixedUpdate()
	{
	}
	void ArcanaScript::Render()
	{
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
		animator->GetCompleteEvent(L"WindSlash") = std::bind(&ArcanaScript::completedMeleeProjectile, this);

		// Projectile
	}
#pragma endregion
#pragma region Collision
	void ArcanaScript::OnCollisionEnter(Collider2D* collider)
	{
		FindTargetType(collider);
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

#pragma region Player Call
	void ArcanaScript::ActiveArcana(Arcana* arcana, bool isRight)
	{
		mArcana = arcana;
		mArcanaState = eProjectileState::Active;	// ���Ŀ� bool������ ����
		mProjectileAbled = true;
		mIsRight = isRight;
		mTransform->SetPosition(mStartPos);
		GetOwner()->OnActive();
		playAnimation();
	}
	void ArcanaScript::playAnimation()
	{
		if (eArcanaName::WindSlash == mArcana->arcanaInfo->name)
		{
			mTransform->SetScale(Vector3(2.0f, 1.5f, 1.0f));
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
#pragma endregion

	void ArcanaScript::projectileProcess()
	{
		projectileEndCheck();
		projectileMove();
	}
	void ArcanaScript::projectileEndCheck()
	{
		endConditionRangeProjectile();

		// Disable ���¶��
		//if (eProjectileState::Disabled == mArcanaState)		// ���Ŀ� bool������ ����
		//{
		//	resetProjectile();
		//}
		if (false == mProjectileAbled)
		{
			resetProjectile();
		}
	}
	void ArcanaScript::projectileMove()
	{
		if (eArcanaName::WindSlash == mArcana->arcanaInfo->name)
		{
			Vector3 movePos = mStartPos;
			movePos += mTransform->Up() * mArcana->projectileStat->speed * 0.3f;
			mTransform->SetPosition(movePos);
		}
		else if (eArcanaName::DragonArc == mArcana->arcanaInfo->name)
		{
			Vector3 pos = mTransform->GetPosition(); 
			pos += mTransform->Up() * mArcana->projectileStat->speed * Time::DeltaTime();
			mTransform->SetPosition(pos);
			// cos ���� ��� �߰��ϱ�
		}
	}
	void ArcanaScript::resetProjectile()
	{
		// ��ġ �ʱ�ȭ
		mTransform->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		mTransform->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		GetOwner()->OnPause();
	}

	// ���� �Լ�
	void ArcanaScript::completedMeleeProjectile()
	{
		mArcanaState = eProjectileState::Disabled;		// bool�� ����
		mProjectileAbled = false;
	}
	void ArcanaScript::endConditionRangeProjectile()
	{
		if (nullptr == mArcana)
			return;
		
		if (eArcanaCategory::Range == mArcana->arcanaInfo->category)
		{
			// �����Ÿ� �̵��ϸ� ����
			Vector3 currentPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			
			if (mArcana->projectileStat->range <= Vector3::Distance(mStartPos, currentPos))
			{
				mArcanaState = eProjectileState::Disabled;		// bool�� ����
				mProjectileAbled = false;
			}
		}
	}
}
