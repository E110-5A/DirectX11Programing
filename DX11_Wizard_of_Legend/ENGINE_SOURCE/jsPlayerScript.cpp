#include "jsPlayerScript.h"

#include "jsInput.h"
#include "jsTime.h"

#include "jsResources.h"

#include "jsGameObject.h"

#include "jsTransform.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"
#include "jsArcanaScript.h"


// 벡터 방향
#define V2DOWN 0,-1
#define V2RIGHT 1,0
#define V2LEFT -1,0
#define V2UP 0,1

// 라디안 방향
#define TOP		0
#define BOTTOM	-3.14
#define RIGHT	-1.57
#define LEFT	1.57

namespace js
{
	PlayerScript::PlayerScript()
		: Script()
		, mState(eState::Idle)
		, mMoveSpeed(3.0f)
		, mMoveDir(Vector2(V2DOWN))
		, mMouseDir(Vector2::Zero)
		, mProjectiles{}, mAA{}, mSkill{}, mDash{}, mSpecial{}, mUltimate{}
		, mBasicAnimationType(true)
	{
	}
		
	PlayerScript::~PlayerScript()
	{
	}

#pragma region 초기화
	void PlayerScript::Initialize()
	{
		createAnimation();
		addEvents();
		// 기술 세팅하기
		// 근거리 평타 (콤보 기능 넣을것!)
		initializeArcana(mAA, eArcanaCategory::Projectile, eArcanaType::AA, eStagger::Light
			, 6.0f, 5.0f, 5.0f, 1.4f, 2, 0.9, 0.14f);
		// Dragon_Arc
		initializeArcana(mSkill, eArcanaCategory::Projectile, eArcanaType::Skill, eStagger::Normal
			, 6.5f, 12.0f, 5.0f, 3.0f, 3, 1.0f, 0.12f);
		// 어깨빵
		initializeArcana(mDash, eArcanaCategory::Melee, eArcanaType::Dash, eStagger::Light
			, 3.0f, 20.0f, 5.0f, 1.0f, 1, 0.9f, 0.4f);
		// 부채꼴로 광역 투사체?
		initializeArcana(mSpecial, eArcanaCategory::Projectile, eArcanaType::Special, eStagger::Normal
			, 6.5f, 10.0f, 5.0f, 5.0f, 4, 0.9f, 0.1f);
		// Shearing_Chain 근거리 죽창
		initializeArcana(mUltimate, eArcanaCategory::Melee, eArcanaType::Ultimate, eStagger::Heave
			, 6.5f, 7.0f, 5.0f, 7.0f, 4, 0.9f, 0.1f);
	}
	
	void PlayerScript::createAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PlayerSpriteSheet", L"Player\\PlayerSpriteSheet.png");
		// Idle
		{
			animator->Create(L"PlayerIdleDown", texture, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerIdleRight", texture, Vector2(48.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerIdleLeft", texture, Vector2(96.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerIdleUp", texture, Vector2(144.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		}
		// Move
		{
			animator->Create(L"PlayerRunDown",	texture, Vector2(0.0f, 49.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunRight", texture, Vector2(0.0f, 97.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunLeft",	texture, Vector2(0.0f, 145.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunUp",	texture, Vector2(0.0f, 193.0f), defaultSize, Vector2::Zero, 10, 0.08f);
		}
		// Hurt
		{
			animator->Create(L"PlayerHurtDown", texture, Vector2(0.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerHurtRight", texture, Vector2(48.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerHurtLeft", texture, Vector2(96.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerHurtUp", texture, Vector2(144.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		}
		
		// Dash
		{
			animator->Create(L"PlayerDashDown", texture, Vector2(0.0f, 242.0f),		defaultSize, Vector2::Zero, 4, 0.1f);
			animator->Create(L"PlayerDashRight", texture, Vector2(0.0f, 290.0f),	defaultSize, Vector2::Zero, 6, 0.1f);
			animator->Create(L"PlayerDashLeft", texture, Vector2(0.0f, 338.0f),		defaultSize, Vector2::Zero, 6, 0.1f);
			animator->Create(L"PlayerDashUp", texture, Vector2(0.0f, 386.0f),		defaultSize, Vector2::Zero, 5, 0.1f);
		}
		// Basic
		{
			animator->Create(L"PlayerBackhandDown", texture, Vector2(0.0f, 435.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandRight", texture, Vector2(0.0f, 483.0f),	defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandLeft", texture, Vector2(0.0f, 531.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandUp", texture, Vector2(0.0f, 579.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerForehandDown", texture, Vector2(0.0f, 628.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerForehandRight", texture, Vector2(0.0f, 676.0f),	defaultSize, Vector2::Zero, 8,  0.04f);
			animator->Create(L"PlayerForehandLeft", texture, Vector2(0.0f, 724.0f),		defaultSize, Vector2::Zero, 8,  0.04f);
			animator->Create(L"PlayerForehandUp", texture, Vector2(0.0f, 772.0f),		defaultSize, Vector2::Zero, 12, 0.04f);
		}
		// Slam
		{
			animator->Create(L"PlayerGroundSlamDown", texture, Vector2(0.0f, 821.0f), defaultSize, Vector2::Zero, 10, 0.1f);
			animator->Create(L"PlayerGroundSlamUp", texture, Vector2(0.0f, 869.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		}
		// AOE
		{
			animator->Create(L"PlayerAOEDown", texture, Vector2(0.0f, 918.0f),	defaultSize, Vector2::Zero, 9, 0.085f);
			animator->Create(L"PlayerAOERight", texture, Vector2(0.0f, 966.0f), defaultSize, Vector2::Zero, 12, 0.07f);
			animator->Create(L"PlayerAOELeft", texture, Vector2(0.0f, 1014.0f), defaultSize, Vector2::Zero, 12, 0.07f);
			animator->Create(L"PlayerAOEUp", texture, Vector2(0.0f, 1062.0f),	defaultSize, Vector2::Zero, 11, 0.07f);
		}
		// Kick
		{
			animator->Create(L"PlayerKickDown", texture, Vector2(0.0f, 1159.0f),	defaultSize, Vector2::Zero, 11, 0.06f);
			animator->Create(L"PlayerKickLeft", texture, Vector2(0.0f, 1255.0f),	defaultSize, Vector2::Zero, 9, 0.07f);
			animator->Create(L"PlayerKickRight", texture, Vector2(0.0f, 1207.0f),	defaultSize, Vector2::Zero, 9, 0.07f);
			animator->Create(L"PlayerKickUp", texture, Vector2(0.0f, 1303.0f),		defaultSize, Vector2::Zero, 8, 0.07f);
		}

		animator->Play(L"PlayerIdleDown");
	}
	void PlayerScript::addEvents()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// 예제
		{
		//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		//animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		//animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		//animator->GetActionEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
		}
		// Dash (setIdle, addForce)
		{
			animator->GetActionEvent(L"PlayerDashDown", 3) = std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerDashRight", 3) = std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerDashLeft", 3) = std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerDashUp", 3) = std::bind(&PlayerScript::setIdle, this);
			animator->GetStartEvent(L"PlayerDashDown") = std::bind(&PlayerScript::addForce, this);
			animator->GetStartEvent(L"PlayerDashRight") = std::bind(&PlayerScript::addForce, this);
			animator->GetStartEvent(L"PlayerDashLeft") = std::bind(&PlayerScript::addForce, this);
			animator->GetStartEvent(L"PlayerDashUp") = std::bind(&PlayerScript::addForce, this);
		}
		// Basic (setIdle, playerRush)
		{
			animator->GetCompleteEvent(L"PlayerBackhandDown")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandRight")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandLeft")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandUp")		= std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerBackhandDown", 3)	= std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandRight", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandLeft", 3)	= std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandUp", 3)	= std::bind(&PlayerScript::playerRush, this);

			animator->GetCompleteEvent(L"PlayerForehandDown")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandRight")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandLeft")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandUp")		= std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerForehandDown", 3)	= std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandRight", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandLeft", 3)	= std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandUp", 3)	= std::bind(&PlayerScript::playerRush, this);

		}
		// GroundSlam (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerGroundSlamDown") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerGroundSlamUp") = std::bind(&PlayerScript::setIdle, this);
		}
		// AOE (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerAOEDown") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerAOERight") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerAOELeft") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerAOEUp") = std::bind(&PlayerScript::setIdle, this);
		}
		// Kick (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerKickDown") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerKickLeft") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerKickRight") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerKickUp") = std::bind(&PlayerScript::setIdle, this);
		}
	}

	

	void PlayerScript::initializeArcana(ArcanaInfo& skill, eArcanaCategory category, eArcanaType arcanaType, eStagger stagger
		, float damage, float moveSpeed, float spellRange, float cooldown
		, int maxProjectileCount, float mComboValidTime, float mComboDelayTime)
	{
		skill.spellStat.category = category;
		skill.spellStat.arcanaType = arcanaType;
		skill.spellStat.stagger = stagger;
		skill.spellStat.damage = damage;
		skill.spellStat.moveSpeed = moveSpeed;
		skill.spellStat.spellRange = spellRange;

		skill.cooldownTime = cooldown;
		skill.currentTime = 0.0f;
		skill.cooldownReady = true;

		skill.comboDelay = false;
		skill.comboProcess = false;
		skill.maxComboCount = maxProjectileCount;
		skill.curComboCount = 0;
		skill.comboValidTime = mComboValidTime;
		skill.comboCurrentValidTime = 0.0f;
		skill.comboDelayTime = mComboDelayTime;
		skill.comboCurrentDelayTime = 0.0f;
	}
#pragma endregion

	void PlayerScript::Update()
	{
		// 쿨다운
		cooldown();
		// 각 상태별 행동 (애니메이션 변경)
		switch (mState)
		{
		case eState::Idle:
		{
			Idle();
		}
		break;
		case eState::Move:
		{
			Move();
		}
		break;
		case eState::Dash:
		{
			Dash();
		}
		break;
		case eState::AA:
		{
			AA();
		}
		break;
		case eState::Skill:
		{
			Skill();
		}
		break;
		case eState::Special:
		{
			Special();
		}
		break;
		case eState::Ultimate:
		{
			Ultimate();
		}
		break;
		}

		// 스킬 적용?
		skillProcess();

		calculateMouseDirection();

		// 테스트 (KEY : K, L)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				GetOwner()->Kill();
			}
			if (Input::GetKey(eKeyCode::L))
			{
				GetOwner()->Alive();
			}
		}
	}

	void PlayerScript::Render()
	{
	}

#pragma region 충돌 및 이벤트
	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PlayerScript::Start()
	{
	}
	void PlayerScript::Complete()
	{
	}
	void PlayerScript::End()
	{
	}
	void PlayerScript::Action()
	{
	}
#pragma endregion 


	void PlayerScript::Idle()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// 애니메이션
		if (Input::GetKey(eKeyCode::S))
		{
			animator->Play(L"PlayerRunDown");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			animator->Play(L"PlayerRunRight");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			animator->Play(L"PlayerRunLeft");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::W))
		{
			animator->Play(L"PlayerRunUp");
			mState = eState::Move;
		}

		if (Input::GetKey(eKeyCode::LBTN) && true == mAA.cooldownReady)
		{
			playAnimation(eState::AA);
		}
		if (Input::GetKey(eKeyCode::RBTN) && true == mSkill.cooldownReady)
		{
			playAnimation(eState::Skill);
		}
		if (Input::GetKey(eKeyCode::SPACE) && true == mDash.cooldownReady)
		{
			playDashMotion();
		}
		if (Input::GetKey(eKeyCode::F) && true == mSpecial.cooldownReady)
		{
			playAnimation(eState::Special);
		}
		if (Input::GetKey(eKeyCode::Q) && true == mUltimate.cooldownReady)
		{
			playAnimation(eState::Ultimate);
		}

	}
	void PlayerScript::Move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// 이동 로직
		if (Input::GetKey(eKeyCode::S))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Up() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(V2DOWN);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Right() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(V2RIGHT);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Right() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(V2LEFT);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Up() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(V2UP);
		}

		// 애니메이션
		if (Input::GetKey(eKeyCode::LBTN) && true == mAA.cooldownReady)
		{
			playAnimation(eState::AA);
		}
		if (Input::GetKey(eKeyCode::RBTN) && true == mSkill.cooldownReady)
		{
			playAnimation(eState::Skill);
		}
		if (Input::GetKey(eKeyCode::SPACE) && true == mDash.cooldownReady)
		{
			playDashMotion();
		}
		if (Input::GetKey(eKeyCode::F) && true == mSpecial.cooldownReady)
		{
			playAnimation(eState::Special);
		}
		if (Input::GetKey(eKeyCode::Q) && true == mUltimate.cooldownReady)
		{
			playAnimation(eState::Ultimate);
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			animator->Play(L"PlayerIdleDown");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			animator->Play(L"PlayerIdleRight");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			animator->Play(L"PlayerIdleLeft");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			animator->Play(L"PlayerIdleUp");
			mState = eState::Idle;
		}

	}
	void PlayerScript::AA()
	{
		// 애니메이션
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}

		// 로직
		if (Input::GetKey(eKeyCode::LBTN))
		{
			// 대기 상태가 아니라면
			if (false == mAA.comboDelay)
			{
				mAA.comboProcess = true;
			}
		}
	}
	void PlayerScript::Skill()
	{
		// 애니메이션
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
		
		// 로직
		if (Input::GetKey(eKeyCode::RBTN))
		{
			// 대기 상태가 아니라면
			if (false == mSkill.comboDelay)
			{
				mSkill.comboProcess = true;
			}
		}
	}
	void PlayerScript::Dash()
	{
		// 로직
		if (Input::GetKey(eKeyCode::SPACE))
		{
			// 대기 상태가 아니라면
			if (false == mDash.comboDelay)
			{
				mDash.comboProcess = true;
			}
		}
	}
	void PlayerScript::Special()
	{
		// 애니메이션
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
		// 로직
		if (Input::GetKey(eKeyCode::F))
		{
			// 대기 상태가 아니라면
			if (false == mSpecial.comboDelay)
			{
				mSpecial.comboProcess = true;
			}
		}
	}
	void PlayerScript::Ultimate()
	{
		// 애니메이션
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}

		if (Input::GetKey(eKeyCode::Q))
		{
			// 대기 상태가 아니라면
			if (false == mUltimate.comboDelay)
			{
				mUltimate.comboProcess = true;
			}
		}
	}

	void PlayerScript::cooldown()
	{
		comboCooldown(mAA);
		comboCooldown(mSkill);
		comboCooldown(mDash);
		comboCooldown(mSpecial);
		comboCooldown(mUltimate);

		// LBTN
		if (false == mAA.cooldownReady)
		{
			mAA.currentTime += Time::DeltaTime();

			if (mAA.currentTime >= mAA.cooldownTime)
			{
				mAA.cooldownReady = true;
				mAA.currentTime = 0.0f;
			}
		}
		// RBTN
		if (false == mSkill.cooldownReady)
		{
			mSkill.currentTime += Time::DeltaTime();

			if (mSkill.currentTime >= mSkill.cooldownTime)
			{
				mSkill.cooldownReady = true;
				mSkill.currentTime = 0.0f;
			}
		}		
		// SPACE
		if (false == mDash.cooldownReady)
		{
			mDash.currentTime += Time::DeltaTime();

			if (mDash.currentTime >= mDash.cooldownTime)
			{
				mDash.cooldownReady = true;
				mDash.currentTime = 0.0f;
			}
		}
		// F
		if (false == mSpecial.cooldownReady)
		{
			mSpecial.currentTime += Time::DeltaTime();

			if (mSpecial.currentTime >= mSpecial.cooldownTime)
			{
				mSpecial.cooldownReady = true;
				mSpecial.currentTime = 0.0f;
			}
		}
		// Q
		if (false == mUltimate.cooldownReady)
		{
			mUltimate.currentTime += Time::DeltaTime();

			if (mUltimate.currentTime >= mUltimate.cooldownTime)
			{
				mUltimate.cooldownReady = true;
				mUltimate.currentTime = 0.0f;
			}
		}
	}
	void PlayerScript::comboCooldown(ArcanaInfo& info)
	{
		// 콤보
		if (true == info.comboDelay)
			info.comboCurrentDelayTime += Time::DeltaTime();
		if (true == info.comboProcess)
			info.comboCurrentValidTime += Time::DeltaTime();

		if (info.comboCurrentDelayTime >= info.comboDelayTime)
		{
			info.comboDelay = false;
			info.comboCurrentDelayTime = 0.0f;
		}
	}

	void PlayerScript::skillProcess()
	{		
		if (true == mAA.cooldownReady)
		{
			if (true == mAA.comboProcess)
			{
				// 콤보 카운트 넘겼는지 확인
				if (comboCountOutCheck(mAA))
					return;
				//// 콤보 유효시간 넘겼는지 확인
				//if (comboValidOutCheck(mAA))
				//	return;

				// 문제없으면 평타 때림!
				if (false == mAA.comboDelay)
				{
					++mAA.curComboCount;
					mAA.comboDelay = true;
					shoot(mAA);
				}				
			}
		}		
		if (true == mSkill.cooldownReady)
		{
			if (true == mSkill.comboProcess)
			{
				// 콤보 카운트 넘겼는지 확인
				if (comboCountOutCheck(mSkill))
					return;
				//// 콤보 유효시간 넘겼는지 확인
				//if (comboValidOutCheck(mSkill))
				//	return;

				// 문제없으면 평타 때림!
				if (false == mSkill.comboDelay)
				{
					++mSkill.curComboCount;
					mSkill.comboDelay = true;
					shoot(mSkill);
				}
			}
		}
		if (true == mDash.cooldownReady)
		{
			mDash.cooldownReady = false;
		}
		if (true == mSpecial.cooldownReady)
		{
			if (true == mSpecial.comboProcess)
			{
				// 콤보 카운트 넘겼는지 확인
				if (comboCountOutCheck(mSpecial))
					return;
				//// 콤보 유효시간 넘겼는지 확인
				//if (comboValidOutCheck(mSpecial))
				//	return;

				// 문제없으면 평타 때림!
				if (false == mSpecial.comboDelay)
				{
					++mSpecial.curComboCount;
					mSpecial.comboDelay = true;
					shoot(mSpecial);
				}
			}
		}
		if (true == mUltimate.cooldownReady)
		{
			if (true == mUltimate.comboProcess)
			{
				// 콤보 카운트 넘겼는지 확인
				if (comboCountOutCheck(mUltimate))
					return;
				//// 콤보 유효시간 넘겼는지 확인
				//if (comboValidOutCheck(mUltimate))
				//	return;

				// 문제없으면 평타 때림!
				if (false == mUltimate.comboDelay)
				{
					++mUltimate.curComboCount;
					mUltimate.comboDelay = true;
					shoot(mUltimate);
				}
			}
		}
	}

	// 아직 안씀
	void PlayerScript::shoot(ArcanaInfo& info)
	{
		// 방향 계산
		float angle = calculateRotateAngle();
		
		// 투사체 찾기
		int poolIndex = findProjectilePool();

		if (-1 != poolIndex)
		{
			// 투사체 회전
			projectileRotates(mProjectiles[poolIndex], angle);
			
			// 투사체를 내 위치로 옮기기
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Transform* targetTr = mProjectiles[poolIndex]->GetOwner()->GetComponent<Transform>();
			targetTr->SetPosition(tr->GetPosition());

			mProjectiles[poolIndex]->ActiveArcana(info);
		}
		
	}

	void PlayerScript::calculateMouseDirection()
	{
		// 마우스 방향 구하기
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector3 myPosistion = myTr->GetPosition();
		Vector3 mousePosition = Input::GetMouseWorldPosition();
		Vector3 myDir = mousePosition - myPosistion;
		mMouseDir = Vector2(myDir.x, myDir.y);
		mMouseDir.Normalize();
	}
	float PlayerScript::calculateRotateAngle()
	{
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		float angle = atan2(mMouseDir.y, mMouseDir.x) - atan2(myTr->Up().y, myTr->Up().x);
		return angle;
	}
	void PlayerScript::setPlayerDirection(float angle)
	{
		//  방향 전환 :  TOP | RIGHT | BOTTOM | LEFT 
		if ((TOP + 0.78) >= angle && (TOP - 0.78) <= angle)
			mMoveDir = Vector2(0, 1);
		else if ((RIGHT + 0.78) >= angle && (RIGHT - 0.78) <= angle)
			mMoveDir = Vector2(1, 0);
		else if ((BOTTOM + 0.78) >= angle && (BOTTOM - 0.78) <= angle)
			mMoveDir = Vector2(0, -1);
		else
			mMoveDir = Vector2(-1, 0);
	}

	int PlayerScript::findProjectilePool()
	{
		for (int index = 0; index < PROJECTILE_POOL; ++index)
		{
			// 없으면 다음으로
			if (nullptr == mProjectiles[index])
				continue;
			// 사용중이면 다음으로
			if (eArcanaState::Disabled == mProjectiles[index]->GetArcanaState())
			{
				return index;
			}
			else
			{
				if (index == 63)
					int a = 0;
			}
			/*projectileRotate(angle);
			activeProjectile();*/
		}
		return -1;
	}
	void PlayerScript::projectileRotates(ArcanaScript* target, float angle)
	{
		Transform* targetTr = target->GetOwner()->GetComponent<Transform>();
		targetTr->SetRotation(Vector3(0.0f, 0.0f, angle));
	}
	
	void PlayerScript::playAnimation(eState changeState)
	{

		Animator* animator = GetOwner()->GetComponent<Animator>();

		// 플레이어 방향 세팅
		float angle = calculateRotateAngle();
		setPlayerDirection(angle);

		// 애니메이션 세팅
		switch (changeState)
		{
		case js::PlayerScript::eState::Idle:
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerIdleDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerIdleRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerIdleLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerIdleUp");
		}
			break;
		case js::PlayerScript::eState::Move:
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerRunDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerRunRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerRunLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerRunUp");
		}
			break;
		case js::PlayerScript::eState::AA:
		{
			playBasicMotion();
		}
			break;
		case js::PlayerScript::eState::Skill:
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerKickDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerKickRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerKickLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerKickUp");
		}
			break;
		case js::PlayerScript::eState::Dash:	// 안씀
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerDashDown", false);
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerDashRight", false);
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerDashLeft", false);
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerDashUp", false);
		}
			break;
		case js::PlayerScript::eState::Special:
		{
			if (1 == mMoveDir.y)
				animator->Play(L"PlayerGroundSlamUp", false);
			else
				animator->Play(L"PlayerGroundSlamDown", false);
		}
			break;
		case js::PlayerScript::eState::Ultimate:
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerAOEDown", false);
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerAOERight", false);
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerAOELeft", false);
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerAOEUp", false);
		}
			break;
		}

		// 상태 변경
		mState = changeState;
	}
	void PlayerScript::playBasicMotion()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (true == mBasicAnimationType)
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerBackhandDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerBackhandRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerBackhandLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerBackhandUp");
			mBasicAnimationType = false;
		}
		else
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerForehandDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerForehandRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerForehandLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerForehandUp");
			mBasicAnimationType = true;
		}
	}
	void PlayerScript::playDashMotion()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		mMoveDir.Normalize();
		if (Vector2(V2DOWN) == mMoveDir)
			animator->Play(L"PlayerDashDown", false);
		if (Vector2(V2RIGHT) == mMoveDir)
			animator->Play(L"PlayerDashRight", false);
		if (Vector2(V2LEFT) == mMoveDir)
			animator->Play(L"PlayerDashLeft", false);
		if (Vector2(V2UP) == mMoveDir)
			animator->Play(L"PlayerDashUp", false);
		mState = eState::Dash;
	}
	void PlayerScript::playerRush()
	{
		// 이동
		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		myRigidbody->SetVelocity(mMouseDir * 11.0f);
	}
	void PlayerScript::addForce()
	{
		Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
		rigidbody->SetVelocity(mMoveDir * 56);
	}

	bool PlayerScript::comboCountOutCheck(ArcanaInfo& info)
	{
		if (info.curComboCount >= info.maxComboCount)
		{
			comboReset(info);
			return true;
		}
		return false;
	}

	bool PlayerScript::comboValidOutCheck(ArcanaInfo& info)
	{
		if (info.comboCurrentValidTime >= info.comboValidTime)
		{			
			comboReset(info);
			return true;
		}
		return false;
	}

	void PlayerScript::comboReset(ArcanaInfo& info)
	{
		// 조건 초기화
		info.SetAble(false);			// 평타 쿨다운 조건
		info.comboProcess = false;		// 콤보 진행 조건
		info.comboDelay = false;		// 콤보 대기시간 초기화
		// 변수 초기화
		info.comboCurrentValidTime = 0.0f;
		info.comboCurrentDelayTime = 0.0f;
		info.curComboCount = 0;
	}

}