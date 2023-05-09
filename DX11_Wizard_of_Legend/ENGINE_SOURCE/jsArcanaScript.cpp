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
		// 애니메이션 생성
		createAnimation();

		// 이벤트 생성
		addEvents();
	}

	void ArcanaScript::Update()
	{
		// 비활성시 오브젝트::정지상태
		if (eArcanaState::Disabled == mArcanaState)
			GetOwner()->OnPause();

		projectileProcess();

		//// 비활성 조건 체크
		//endConditionProjectile();
		//// 작동 함수
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
		mTransform->SetPosition(mStartPos);
		GetOwner()->OnActive();
		playAnimation();
	}

	void ArcanaScript::playAnimation()
	{
		if (eArcanaName::WindSlash == mArcana->arcanaInfo->name)
		{
			mTransform->SetScale(Vector3(1.5f, 1.5f, 1.0f));
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
		// Melee 타입인 경우, 애니메이션 재생이 끝나면 조건에 해당함
		// Range 타입인 경우, 사거리를 벗어나면 조건에 해당함
		endConditionProjectile();

		// Disable 상태라면
		if (eArcanaState::Disabled == mArcanaState)
		{
			resetProjectile();
		}

	}

	void ArcanaScript::projectileMove()
	{
		if (eArcanaName::WindSlash == mArcana->arcanaInfo->name)
		{
			Vector3 movePos = mStartPos;
			movePos += mTransform->Up() * mArcana->arcanaStat->moveSpeed * 0.6f;
			mTransform->SetPosition(movePos);
		}
		else if (eArcanaName::DragonArc == mArcana->arcanaInfo->name)
		{
			Vector3 pos = mTransform->GetPosition(); 
			pos += mTransform->Up() * mArcana->arcanaStat->moveSpeed * Time::DeltaTime();
			mTransform->SetPosition(pos);
			// cos 방향 기믹 추가하기
		}
	}

	void ArcanaScript::resetProjectile()
	{
		// 비활성 상태
		mArcanaState = eArcanaState::Disabled;
		// 위치 초기화
		mTransform->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		mTransform->SetScale(Vector3(1.0f, 1.0f, 1.0f));
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
		// 리소스 가져와서 생성
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
	

	// 종료 함수
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
			// 일정거리 이동하면 종료
			Vector3 currentPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			
			if (mArcana->arcanaStat->spellRange <= Vector3::Distance(mStartPos, currentPos))
			{
				mArcanaState = eArcanaState::Disabled;
			}
		}
	}
}
