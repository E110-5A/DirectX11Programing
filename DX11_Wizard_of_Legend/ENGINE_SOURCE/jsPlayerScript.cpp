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

#define RW		1.57
#define RNW		0.785
#define RN		0
#define RNE		-0.785
#define RE		-1.57
#define RSE		-2.335
#define RS		-3.14
#define RSW		-3.925

#define NORTH		 0
#define SOUTH		-3.14
#define EAST		-1.57
#define WEST		 1.57

namespace js
{
	PlayerScript::PlayerScript()
		: mPlayerState(ePlayerState::Idle)
		, mPlayerDir(Vector2(V2DOWN))
		, mMouseDir(Vector2::Zero)
		, mProjectiles{}
		, mTempArcana()
		, mLBtn(), mRBtn(), mSpace(), mQ(), mF(), mR()
		, mYDir(eAxisValue::None)
		, mXDir(eAxisValue::None)
	{
	}
		
	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		CreatureScript::Initialize();
		initializeHealthStat(200.0f, 200.0f, 0.1f, 3.0f);
		initializeOffenceStat(1.0f, 5.0f, 1.7f);

		createAnimation();
		addEvents();

		// 임시 아르카나 생성
		{
			ArcanaInfo* tempInfo = new ArcanaInfo();
			tempInfo->name = eArcanaName::WindSlash;
			tempInfo->category = eArcanaCategory::Melee;
			tempInfo->type = eArcanaType::BasicArcana;
			tempInfo->motion = ePlayerMotion::Basic;
			tempInfo->cooldownReady = true;
			tempInfo->cooldownTime = 0.6f;
			tempInfo->currentTime = 0.0f;

			ArcanaStat* tempStat = new ArcanaStat();
			tempStat->damage = 11.0f;
			tempStat->stagger = 3.0f;
			tempStat->moveSpeed = 0.0f;
			tempStat->spellRange = 0.0f;
			tempStat->projectileDelayTime = 0.0f;
			tempStat->projectileCurrentDelayTime = 0.0f;
			tempStat->maxProjectile = 1;
			tempStat->curProjectile = 0;

			mTempArcana.arcanaInfo = tempInfo;
			mTempArcana.arcanaStat = tempStat;
		}

	}
	
#pragma region 초기화
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
			animator->Create(L"PlayerBackhandDown"	, texture, Vector2(0.0f, 435.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandRight", texture, Vector2(0.0f, 483.0f),	defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandLeft"	, texture, Vector2(0.0f, 531.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandUp"	, texture, Vector2(0.0f, 579.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerForehandDown"	, texture, Vector2(0.0f, 628.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerForehandRight", texture, Vector2(0.0f, 676.0f),	defaultSize, Vector2::Zero, 8,  0.04f);
			animator->Create(L"PlayerForehandLeft"	, texture, Vector2(0.0f, 724.0f),		defaultSize, Vector2::Zero, 8,  0.04f);
			animator->Create(L"PlayerForehandUp"	, texture, Vector2(0.0f, 772.0f),		defaultSize, Vector2::Zero, 12, 0.04f);
		}
		// Slam
		{
			animator->Create(L"PlayerGroundSlamDown"	, texture, Vector2(0.0f, 821.0f), defaultSize, Vector2::Zero, 10, 0.1f);
			animator->Create(L"PlayerGroundSlamUp"		, texture, Vector2(0.0f, 869.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		}
		// AOE
		{
			animator->Create(L"PlayerAOEDown"	, texture, Vector2(0.0f, 918.0f),	defaultSize, Vector2::Zero, 9, 0.085f);
			animator->Create(L"PlayerAOERight"	, texture, Vector2(0.0f, 966.0f), defaultSize, Vector2::Zero, 12, 0.07f);
			animator->Create(L"PlayerAOELeft"	, texture, Vector2(0.0f, 1014.0f), defaultSize, Vector2::Zero, 12, 0.07f);
			animator->Create(L"PlayerAOEUp"	, texture, Vector2(0.0f, 1062.0f),	defaultSize, Vector2::Zero, 11, 0.07f);
		}
		// Kick
		{
			animator->Create(L"PlayerKickDown"	, texture, Vector2(0.0f, 1159.0f),	defaultSize, Vector2::Zero, 11, 0.06f);
			animator->Create(L"PlayerKickLeft"	, texture, Vector2(0.0f, 1255.0f),	defaultSize, Vector2::Zero, 9, 0.07f);
			animator->Create(L"PlayerKickRight", texture, Vector2(0.0f, 1207.0f),	defaultSize, Vector2::Zero, 9, 0.07f);
			animator->Create(L"PlayerKickUp"	, texture, Vector2(0.0f, 1303.0f),		defaultSize, Vector2::Zero, 8, 0.07f);
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
		//// Dash (setIdle, addForce)
		//{
		//	animator->GetActionEvent(L"PlayerDashDown", 3) = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetActionEvent(L"PlayerDashRight", 3) = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetActionEvent(L"PlayerDashLeft", 3) = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetActionEvent(L"PlayerDashUp", 3) = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetStartEvent(L"PlayerDashDown") = std::bind(&PlayerScript::addForceDash, this);
		//	animator->GetStartEvent(L"PlayerDashRight") = std::bind(&PlayerScript::addForceDash, this);
		//	animator->GetStartEvent(L"PlayerDashLeft") = std::bind(&PlayerScript::addForceDash, this);
		//	animator->GetStartEvent(L"PlayerDashUp") = std::bind(&PlayerScript::addForceDash, this);
		//}
		//// Basic (setIdle, playerRush)
		//{
		//	animator->GetCompleteEvent(L"PlayerBackhandDown")	= std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerBackhandRight")	= std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerBackhandLeft")	= std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerBackhandUp")		= std::bind(&PlayerScript::setIdle, this);
		//	animator->GetActionEvent(L"PlayerBackhandDown", 3)	= std::bind(&PlayerScript::playerRush, this);
		//	animator->GetActionEvent(L"PlayerBackhandRight", 3) = std::bind(&PlayerScript::playerRush, this);
		//	animator->GetActionEvent(L"PlayerBackhandLeft", 3)	= std::bind(&PlayerScript::playerRush, this);
		//	animator->GetActionEvent(L"PlayerBackhandUp", 3)	= std::bind(&PlayerScript::playerRush, this);

		//	animator->GetCompleteEvent(L"PlayerForehandDown")	= std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerForehandRight")	= std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerForehandLeft")	= std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerForehandUp")		= std::bind(&PlayerScript::setIdle, this);
		//	animator->GetActionEvent(L"PlayerForehandDown", 3)	= std::bind(&PlayerScript::playerRush, this);
		//	animator->GetActionEvent(L"PlayerForehandRight", 3) = std::bind(&PlayerScript::playerRush, this);
		//	animator->GetActionEvent(L"PlayerForehandLeft", 3)	= std::bind(&PlayerScript::playerRush, this);
		//	animator->GetActionEvent(L"PlayerForehandUp", 3)	= std::bind(&PlayerScript::playerRush, this);

		//}
		//// GroundSlam (setIdle)
		//{
		//	animator->GetCompleteEvent(L"PlayerGroundSlamDown") = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerGroundSlamUp") = std::bind(&PlayerScript::setIdle, this);
		//}
		//// AOE (setIdle)
		//{
		//	animator->GetCompleteEvent(L"PlayerAOEDown") = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerAOERight") = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerAOELeft") = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerAOEUp") = std::bind(&PlayerScript::setIdle, this);
		//}
		//// Kick (setIdle)
		//{
		//	animator->GetCompleteEvent(L"PlayerKickDown") = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerKickLeft") = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerKickRight") = std::bind(&PlayerScript::setIdle, this);
		//	animator->GetCompleteEvent(L"PlayerKickUp") = std::bind(&PlayerScript::setIdle, this);
		//}
	}

#pragma endregion

	void PlayerScript::Update()
	{
		calculateMouseDirection();
		calculatePlayerDirection();
		switch (mPlayerState)
		{
		case js::PlayerScript::ePlayerState::Idle:
		{
			Idle();
		}
			break;
		case js::PlayerScript::ePlayerState::Move:
		{
			Move();
		}
			break;
		case js::PlayerScript::ePlayerState::LBtn:
		{
			LBtn();
		}
			break;
		case js::PlayerScript::ePlayerState::RBtn:
		{
			RBtn();
		}
			break;
		case js::PlayerScript::ePlayerState::Space:
		{
			Space();
		}
			break;
		case js::PlayerScript::ePlayerState::Q:
		{
			Q();
		}
			break;
		case js::PlayerScript::ePlayerState::F:
		{
			F();
		}
			break;
		case js::PlayerScript::ePlayerState::R:
		{
			R();
		}
			break;
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
		if (Input::GetKey(eKeyCode::S))
		{
			// 방향 전환
			changePlayerDirection(eAxisValue::Down, true);
			// 상태 바꾸기
			changeState(ePlayerState::Move);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			// 방향 전환
			changePlayerDirection(eAxisValue::Up, false);
			// 상태 바꾸기
			changeState(ePlayerState::Move);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			// 방향 전환
			changePlayerDirection(eAxisValue::Down, false);
			// 상태 바꾸기
			changeState(ePlayerState::Move);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKey(eKeyCode::W))
		{
			// 방향 전환
			changePlayerDirection(eAxisValue::Up, true);
			// 상태 바꾸기
			changeState(ePlayerState::Move);
			// 애니메이션 재생	
			playAnimation();
		}

		if (Input::GetKey(eKeyCode::LBTN)) 
		{
		}
		if (Input::GetKey(eKeyCode::RBTN))
		{
		}
		if (Input::GetKey(eKeyCode::SPACE))
		{
		}
		if (Input::GetKey(eKeyCode::F))
		{
		}
		if (Input::GetKey(eKeyCode::Q))
		{
		}
	}

	void PlayerScript::Move()
	{
		// 이동 로직
		if (Input::GetKey(eKeyCode::S))
		{
			Vector3 pos = mTransform->GetPosition();
			pos += -mTransform->Up() * mHealthStat.moveSpeed * Time::DeltaTime();
			mTransform->SetPosition(pos);
			changePlayerDirection(eAxisValue::Down, true);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = mTransform->GetPosition();
			pos += mTransform->Right() * mHealthStat.moveSpeed * Time::DeltaTime();
			mTransform->SetPosition(pos);
			changePlayerDirection(eAxisValue::Up, false);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = mTransform->GetPosition();
			pos += -mTransform->Right() * mHealthStat.moveSpeed * Time::DeltaTime();
			mTransform->SetPosition(pos);
			changePlayerDirection(eAxisValue::Down, false);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Vector3 pos = mTransform->GetPosition();
			pos += mTransform->Up() * mHealthStat.moveSpeed * Time::DeltaTime();
			mTransform->SetPosition(pos);
			changePlayerDirection(eAxisValue::Up, true);
		}

		if (Input::GetKey(eKeyCode::LBTN))
		{
			// 상태 바꾸기
			changeState(ePlayerState::LBtn);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKey(eKeyCode::RBTN))
		{
			// 상태 바꾸기
			changeState(ePlayerState::RBtn);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKey(eKeyCode::SPACE))
		{
			// 상태 바꾸기
			changeState(ePlayerState::Space);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKey(eKeyCode::F))
		{
			// 상태 바꾸기
			changeState(ePlayerState::F);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKey(eKeyCode::Q))
		{
			// 상태 바꾸기
			changeState(ePlayerState::Q);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKey(eKeyCode::R))
		{
			// 상태 바꾸기
			changeState(ePlayerState::R);
			// 애니메이션 재생	
			playAnimation();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			// 방향 전환
			changePlayerDirection(eAxisValue::Down, true);
			// 상태 바꾸기
			changeState(ePlayerState::Idle);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			// 방향 전환
			changePlayerDirection(eAxisValue::Up, false);
			// 상태 바꾸기
			changeState(ePlayerState::Idle);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			// 방향 전환
			changePlayerDirection(eAxisValue::Down, false);
			// 상태 바꾸기
			changeState(ePlayerState::Idle);
			// 애니메이션 재생	
			playAnimation();
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			// 방향 전환
			changePlayerDirection(eAxisValue::Up, true);
			// 상태 바꾸기
			changeState(ePlayerState::Idle);
			// 애니메이션 재생	
			playAnimation();
		}

	}

	void PlayerScript::LBtn()
	{
	}

	void PlayerScript::RBtn()
	{
	}

	void PlayerScript::Space()
	{
	}

	void PlayerScript::Q()
	{
	}

	void PlayerScript::F()
	{
	}

	void PlayerScript::R()
	{
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
	void PlayerScript::calculatePlayerDirection()
	{
		int x = 0;
		int y = 0;

		if (eAxisValue::None == mXDir)
			x = 0;
		if (eAxisValue::None == mYDir)
			y = 0;

		if (eAxisValue::Up == mXDir)
			x = 1;
		if (eAxisValue::Up == mYDir)
			y = 1;
		if (eAxisValue::Down == mXDir)
			x = -1;
		if (eAxisValue::Down == mYDir)
			y = -1;

		Vector2 curDir(x, y);
		curDir.Normalize();
		mCurrentDirection = curDir;
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
		}
		return -1;
	}
	void PlayerScript::projectileRotates(ArcanaScript* target, float angle)
	{
		Transform* targetTr = target->GetOwner()->GetComponent<Transform>();
		targetTr->SetRotation(Vector3(0.0f, 0.0f, angle));
	}


	void PlayerScript::rotatePlayerDirection(float angle)
	{
		// NORTH
		if ((NORTH + 0.78) >= angle && (NORTH - 0.78) <= angle)
			mAnimationDirection = Vector2(0, 1);
		// EAST
		else if ((EAST + 0.78) >= angle && (EAST - 0.78) <= angle)
			mAnimationDirection = Vector2(1, 0);
		// SOUTH
		else if ((SOUTH + 0.78) >= angle && (SOUTH - 0.78) <= angle)
			mAnimationDirection = Vector2(0, -1);
		// WEST
		else
			mAnimationDirection = Vector2(-1, 0);
	}
	void PlayerScript::changePlayerDirection(eAxisValue direction, bool isYAxis)
	{
		// AnimationDirection을 변경하고, XDir, YDir 값을 변경함
		if (isYAxis)
		{
			if (eAxisValue::Up == direction)
				mAnimationDirection = Vector2(0, 1);
			if (eAxisValue::Down == direction)
				mAnimationDirection = Vector2(0, -1);

			if (direction != mYDir && eAxisValue::None != mYDir)
				mYDir = eAxisValue::None;
		}
		else
		{
			if (eAxisValue::Up == direction)
				mAnimationDirection = Vector2(1, 0);
			if (eAxisValue::Down == direction)
				mAnimationDirection = Vector2(-1, 0);

			if (direction != mXDir && eAxisValue::None != mXDir)
				mXDir = eAxisValue::None;
		}
	}

	
	void PlayerScript::playerRush()
	{
		// 이동
		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		myRigidbody->SetVelocity(mMouseDir * 11.0f);
	}
	void PlayerScript::addForceDash()
	{
		Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
		rigidbody->SetVelocity(mCurrentDirection * 56);
	}

#pragma region 애니메이션 실행함수
	void PlayerScript::playAnimation()
	{
		switch (mPlayerState)
		{
		case js::PlayerScript::ePlayerState::Idle:
		{
			playIdleAnimation();
		}
		break;
		case js::PlayerScript::ePlayerState::Move:
		{
			playMoveAnimation();
		}
		break;
		case js::PlayerScript::ePlayerState::LBtn:
		{
			findAnimation(mLBtn.arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::RBtn:
		{
			findAnimation(mRBtn.arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::Space:
		{
			findAnimation(mSpace.arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::Q:
		{
			findAnimation(mQ.arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::F:
		{
			findAnimation(mF.arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::R:
		{
			findAnimation(mR.arcanaInfo->motion);
		}
		break;
		}
	}
	void PlayerScript::findAnimation(ePlayerMotion motion)
	{
		if (ePlayerMotion::Basic == motion)
			playBasicAnimation();
		if (ePlayerMotion::Dash == motion)
			playDashAnimation();
		if (ePlayerMotion::GroundSlam == motion)
			playGroundSlamAnimation();
		if (ePlayerMotion::AOE == motion)
			playAOEAnimation();
		if (ePlayerMotion::Kick == motion)
			playKickAnimation();
	}
	void PlayerScript::playIdleAnimation()
	{
		if (Vector2(V2DOWN) == mAnimationDirection)
			mAnimator->Play(L"PlayerIdleDown");
		if (Vector2(V2RIGHT) == mAnimationDirection)
			mAnimator->Play(L"PlayerIdleRight");
		if (Vector2(V2LEFT) == mAnimationDirection)
			mAnimator->Play(L"PlayerIdleLeft");
		if (Vector2(V2UP) == mAnimationDirection)
			mAnimator->Play(L"PlayerIdleUp");
	}
	void PlayerScript::playMoveAnimation()
	{
		if (Vector2(V2DOWN) == mAnimationDirection)
			mAnimator->Play(L"PlayerRunDown");
		if (Vector2(V2RIGHT) == mAnimationDirection)
			mAnimator->Play(L"PlayerRunRight");
		if (Vector2(V2LEFT) == mAnimationDirection)
			mAnimator->Play(L"PlayerRunLeft");
		if (Vector2(V2UP) == mAnimationDirection)
			mAnimator->Play(L"PlayerRunUp");
	}
	void PlayerScript::playBasicAnimation()
	{
		if (true == mBasicAnimationType)
		{
			if (Vector2(V2DOWN) == mAnimationDirection)
				mAnimator->Play(L"PlayerBackhandDown", false);
			if (Vector2(V2RIGHT) == mAnimationDirection)
				mAnimator->Play(L"PlayerBackhandRight", false);
			if (Vector2(V2LEFT) == mAnimationDirection)
				mAnimator->Play(L"PlayerBackhandLeft", false);
			if (Vector2(V2UP) == mAnimationDirection)
				mAnimator->Play(L"PlayerBackhandUp", false);
			mBasicAnimationType = false;
		}
		else
		{
			if (Vector2(V2DOWN) == mAnimationDirection)
				mAnimator->Play(L"PlayerForehandDown", false);
			if (Vector2(V2RIGHT) == mAnimationDirection)
				mAnimator->Play(L"PlayerForehandRight", false);
			if (Vector2(V2LEFT) == mAnimationDirection)
				mAnimator->Play(L"PlayerForehandLeft", false);
			if (Vector2(V2UP) == mAnimationDirection)
				mAnimator->Play(L"PlayerForehandUp", false);
			mBasicAnimationType = true;
		}
	}
	void PlayerScript::playGroundSlamAnimation()
	{
		mAnimator->Play(L"PlayerGroundSlamDown", false);
	}
	void PlayerScript::playAOEAnimation()
	{
		if (Vector2(V2DOWN) == mAnimationDirection)
			mAnimator->Play(L"PlayerAOEDown", false);
		if (Vector2(V2RIGHT) == mAnimationDirection)
			mAnimator->Play(L"PlayerAOERight", false);
		if (Vector2(V2LEFT) == mAnimationDirection)
			mAnimator->Play(L"PlayerAOELeft", false);
		if (Vector2(V2UP) == mAnimationDirection)
			mAnimator->Play(L"PlayerAOEUp", false);
	}		
	void PlayerScript::playKickAnimation()
	{
		if (Vector2(V2DOWN) == mAnimationDirection)
			mAnimator->Play(L"PlayerKickDown", false);
		if (Vector2(V2RIGHT) == mAnimationDirection)
			mAnimator->Play(L"PlayerKickRight", false);
		if (Vector2(V2LEFT) == mAnimationDirection)
			mAnimator->Play(L"PlayerKickLeft", false);
		if (Vector2(V2UP) == mAnimationDirection)
			mAnimator->Play(L"PlayerKickUp", false);
	}
	void PlayerScript::playDashAnimation()
	{
		if (Vector2(V2DOWN) == mAnimationDirection)
			mAnimator->Play(L"PlayerDashDown", false);
		if (Vector2(V2RIGHT) == mAnimationDirection)
			mAnimator->Play(L"PlayerDashRight", false);
		if (Vector2(V2LEFT) == mAnimationDirection)
			mAnimator->Play(L"PlayerDashLeft", false);
		if (Vector2(V2UP) == mAnimationDirection)
			mAnimator->Play(L"PlayerDashUp", false);
	}
#pragma endregion

	void PlayerScript::changeState(ePlayerState changeState)
	{
		mPlayerState = changeState;
	}
}