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
		// 애니메이션 생성
		createAnimation();

		// 이벤트 생성
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
		animator->GetCompleteEvent(L"WindSlash") = std::bind(&ProjectileScript::Disappear, this);

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
			// cos 방향 기믹 추가하기
		}
	}
	void ArcanaScript::resetProjectile()
	{
		// 위치 초기화
		mTransform->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		mTransform->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		GetOwner()->OnPause();
	}

	void ArcanaScript::endConditionRangeProjectile()
	{
		if (nullptr == mArcana)
			return;
		
		if (eArcanaCategory::Range == mArcana->arcanaInfo->category)
		{
			// 일정거리 이동하면 종료
			Vector3 currentPos = GetOwner()->GetComponent<Transform>()->GetPosition();
			
			if (mArcana->projectileStat->range <= Vector3::Distance(mStartPos, currentPos))
			{
				mProjectileAbled = false;
			}
		}
	}
	void ArcanaScript::CollisionByProjectile(Script* target)
	{
		// 대상의 공격력 값을 가져옴
		ProjectileScript* targetScript = dynamic_cast<ProjectileScript*>(target);
		ProjectileStat targetStat = targetScript->GetProjectileStat(); 

		// 내 투사체가 근접 타입인 경우
		

		if (mProjectileStat.damage <= targetStat.damage) 
		{
			// 내가 더 큰거니까 내 공격력을 깎고, 상대 투사체를 제거
			ProjectileDamaged(targetStat.damage); 
			targetScript->Disappear();
		}
		else
		{
			// 내가 작으니까 상대 공격력을 깎고, 내 투사체를 제거
			targetScript->ProjectileDamaged(mProjectileStat.damage);
			if (eArcanaCategory::Melee != mArcana->arcanaInfo->category)
			{
				Disappear();
			}
		}
	}
	void ArcanaScript::CollisionByCreature(Script* target)
	{
		// 대상에게 공격 호출시키기
		CreatureScript* creature = dynamic_cast<CreatureScript*>(target);

		// 피격 함수명 적절하게 변경해주기
		creature->Damaged(this);
		if (eArcanaCategory::Melee != mArcana->arcanaInfo->category)
		{
			Disappear();
		}
	}
}
