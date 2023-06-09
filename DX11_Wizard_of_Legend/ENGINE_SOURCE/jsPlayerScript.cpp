#include "jsPlayerScript.h"

#include "jsInput.h"
#include "jsTime.h"

#include "jsResources.h"

#include "jsGameObject.h"

#include "jsTransform.h"
#include "jsAnimator.h"
#include "jsArcanaScript.h"


// ���� ����
#define V2DOWN		0,-1
#define V2RIGHT		1,0
#define V2LEFT		-1,0
#define V2UP		0,1

#define V2W			-1.0f	,0
#define V2NW		-0.7f	,0.7f
#define V2N			0		,1.0f
#define V2NE		0.7f	,0.7f
#define V2E			1.0f	,0
#define V2SE		0.7f	,-0.7f
#define V2S			0		,-1.0f
#define V2SW		-0.7f	,-0.7f

// ���� ����

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
		: mPlayerState(ePlayerState::IDLE)
		, mMouseDir(Vector2::Zero)
		, mProjectiles{}
		, mInventory()
		, mYDir(eAxisValue::None)
		, mXDir(eAxisValue::None)
		, mArcanaUsing(false)
		, mBasicAnimationType(true)
		, mIsProjectileRight(true)
		, mArcanaStartAngle(0.0f)
		, mSprintReady(false)
		, mSprintTime(1.5f)
		, mSprintCheck(0.0f)
		, mSprintSpeed(0.0f)
	{

	}
	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		CreatureScript::Initialize();
		initializeHealthStat(200.0f, 0.1f, 4.0f, 30.0f);
		initializeOffenceStat(1.0f, 5.0f, 1.7f);

		createAnimation();
		addEvents();
		
		mCollider->SetSize(Vector2(0.4f, 0.35f));
		mCollider->SetCenter(Vector2(0.0f, -0.25f));
		startingArcana();
	}
#pragma region �ʱ�ȭ
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
			animator->Create(L"PlayerRunDown", texture, Vector2(0.0f, 49.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunRight", texture, Vector2(0.0f, 97.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunLeft", texture, Vector2(0.0f, 145.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunUp", texture, Vector2(0.0f, 193.0f), defaultSize, Vector2::Zero, 10, 0.08f);
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
			animator->Create(L"PlayerDashDown", texture, Vector2(0.0f, 242.0f), defaultSize, Vector2::Zero, 4, 0.1f);
			animator->Create(L"PlayerDashRight", texture, Vector2(0.0f, 290.0f), defaultSize, Vector2::Zero, 6, 0.1f);
			animator->Create(L"PlayerDashLeft", texture, Vector2(0.0f, 338.0f), defaultSize, Vector2::Zero, 6, 0.1f);
			animator->Create(L"PlayerDashUp", texture, Vector2(0.0f, 386.0f), defaultSize, Vector2::Zero, 5, 0.1f);
		}
		// Basic
		{
			animator->Create(L"PlayerBackhandDown", texture, Vector2(0.0f, 435.0f), defaultSize, Vector2::Zero, 9, 0.04f);
			animator->Create(L"PlayerBackhandRight", texture, Vector2(0.0f, 483.0f), defaultSize, Vector2::Zero, 9, 0.04f);
			animator->Create(L"PlayerBackhandLeft", texture, Vector2(0.0f, 531.0f), defaultSize, Vector2::Zero, 9, 0.04f);
			animator->Create(L"PlayerBackhandUp", texture, Vector2(0.0f, 579.0f), defaultSize, Vector2::Zero, 9, 0.04f);
			animator->Create(L"PlayerForehandDown", texture, Vector2(0.0f, 628.0f), defaultSize, Vector2::Zero, 9, 0.04f);
			animator->Create(L"PlayerForehandRight", texture, Vector2(0.0f, 676.0f), defaultSize, Vector2::Zero, 8, 0.04f);
			animator->Create(L"PlayerForehandLeft", texture, Vector2(0.0f, 724.0f), defaultSize, Vector2::Zero, 8, 0.04f);
			animator->Create(L"PlayerForehandUp", texture, Vector2(0.0f, 772.0f), defaultSize, Vector2::Zero, 12, 0.04f);
		}
		// Slam
		{
			animator->Create(L"PlayerGroundSlamDown", texture, Vector2(0.0f, 821.0f), defaultSize, Vector2::Zero, 10, 0.1f);
			animator->Create(L"PlayerGroundSlamUp", texture, Vector2(0.0f, 869.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		}
		// AOE
		{
			animator->Create(L"PlayerAOEDown", texture, Vector2(0.0f, 918.0f), defaultSize, Vector2::Zero, 9, 0.085f);
			animator->Create(L"PlayerAOERight", texture, Vector2(0.0f, 966.0f), defaultSize, Vector2::Zero, 12, 0.07f);
			animator->Create(L"PlayerAOELeft", texture, Vector2(0.0f, 1014.0f), defaultSize, Vector2::Zero, 12, 0.07f);
			animator->Create(L"PlayerAOEUp", texture, Vector2(0.0f, 1062.0f), defaultSize, Vector2::Zero, 11, 0.07f);
		}
		// Kick
		{
			animator->Create(L"PlayerKickDown", texture, Vector2(0.0f, 1159.0f), defaultSize, Vector2::Zero, 11, 0.06f);
			animator->Create(L"PlayerKickLeft", texture, Vector2(0.0f, 1255.0f), defaultSize, Vector2::Zero, 9, 0.07f);
			animator->Create(L"PlayerKickRight", texture, Vector2(0.0f, 1207.0f), defaultSize, Vector2::Zero, 9, 0.07f);
			animator->Create(L"PlayerKickUp", texture, Vector2(0.0f, 1303.0f), defaultSize, Vector2::Zero, 8, 0.07f);
		}
		animator->Play(L"PlayerIdleDown");
	}
	void PlayerScript::addEvents()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// ����
		{
			//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
			//animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
			//animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
			//animator->GetActionEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
		}

		// Dash (setIdle, addForce)
		{
			animator->GetActionEvent(L"PlayerDashDown", 3) = std::bind(&PlayerScript::retIdle, this);
			animator->GetActionEvent(L"PlayerDashRight", 3) = std::bind(&PlayerScript::retIdle, this);
			animator->GetActionEvent(L"PlayerDashLeft", 3) = std::bind(&PlayerScript::retIdle, this);
			animator->GetActionEvent(L"PlayerDashUp", 3) = std::bind(&PlayerScript::retIdle, this);
			animator->GetStartEvent(L"PlayerDashDown")		= std::bind(&PlayerScript::dashForce, this);
			animator->GetStartEvent(L"PlayerDashRight")	= std::bind(&PlayerScript::dashForce, this);
			animator->GetStartEvent(L"PlayerDashLeft")		= std::bind(&PlayerScript::dashForce, this);
			animator->GetStartEvent(L"PlayerDashUp")		= std::bind(&PlayerScript::dashForce, this);
		}

		// Basic (setIdle, playerRush)
		{
			animator->GetCompleteEvent(L"PlayerBackhandDown") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandRight") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandLeft") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandUp") = std::bind(&PlayerScript::retIdle, this);
			// animator->GetActionEvent(L"PlayerBackhandDown", 3) = std::bind(&PlayerScript::playerRush, this);
			// animator->GetActionEvent(L"PlayerBackhandRight", 3) = std::bind(&PlayerScript::playerRush, this);
			// animator->GetActionEvent(L"PlayerBackhandLeft", 3) = std::bind(&PlayerScript::playerRush, this);
			// animator->GetActionEvent(L"PlayerBackhandUp", 3) = std::bind(&PlayerScript::playerRush, this);

			animator->GetCompleteEvent(L"PlayerForehandDown") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandRight") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandLeft") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandUp") = std::bind(&PlayerScript::retIdle, this);
			// animator->GetActionEvent(L"PlayerForehandDown", 3) = std::bind(&PlayerScript::playerRush, this);
			// animator->GetActionEvent(L"PlayerForehandRight", 3) = std::bind(&PlayerScript::playerRush, this);
			// animator->GetActionEvent(L"PlayerForehandLeft", 3) = std::bind(&PlayerScript::playerRush, this);
			// animator->GetActionEvent(L"PlayerForehandUp", 3) = std::bind(&PlayerScript::playerRush, this);
		}

		// GroundSlam (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerGroundSlamDown") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerGroundSlamUp") = std::bind(&PlayerScript::retIdle, this);
		}

		// AOE (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerAOEDown") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerAOERight") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerAOELeft") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerAOEUp") = std::bind(&PlayerScript::retIdle, this);
		}

		// Kick (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerKickDown") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerKickLeft") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerKickRight") = std::bind(&PlayerScript::retIdle, this);
			animator->GetCompleteEvent(L"PlayerKickUp") = std::bind(&PlayerScript::retIdle, this);
		}
	}

	void PlayerScript::startingArcana()
	{
		mInventory.arcanaBasic = new Arcana();
		{
			ArcanaInfo* tempInfo = new ArcanaInfo();
			tempInfo->name = eArcanaName::WindSlash;
			tempInfo->category = eArcanaCategory::Melee;
			tempInfo->type = eArcanaType::BasicArcana;
			tempInfo->motion = ePlayerMotion::Basic;

			ProjectileConditionValue* tempConditionValue = new ProjectileConditionValue();
			tempConditionValue->cooldownReady = true;
			tempConditionValue->begin = false;
			tempConditionValue->complete = false;
			tempConditionValue->cooldownTime = 0.6f;
			tempConditionValue->currentCooldownTime = 0.0f;
			tempConditionValue->delayTime = 0.0f;
			tempConditionValue->currentDelayTime = 0.0f;
			tempConditionValue->maxCount = 1;
			tempConditionValue->curCount = 0;

			ProjectileStat* tempStat = new ProjectileStat();
			tempStat->damage = 11.0f;
			tempStat->stagger = 3.0f;
			tempStat->speed = 1.0f;
			tempStat->range = 0.0f;

			mInventory.arcanaBasic->arcanaInfo = tempInfo;
			mInventory.arcanaBasic->projectileStat = tempStat;
			mInventory.arcanaBasic->conditionValue = tempConditionValue;
		}
		mInventory.arcanaDash = new Arcana();
		{
			ArcanaInfo* tempInfo = new ArcanaInfo();
			tempInfo->name = eArcanaName::None;
			tempInfo->category = eArcanaCategory::Melee;
			tempInfo->type = eArcanaType::BasicArcana;
			tempInfo->motion = ePlayerMotion::Basic;

			ProjectileConditionValue* tempConditionValue = new ProjectileConditionValue();
			tempConditionValue->cooldownReady = true;
			tempConditionValue->complete = false;
			tempConditionValue->cooldownTime = 3.0f;
			tempConditionValue->currentCooldownTime = 0.0f;
			tempConditionValue->delayTime = 0.0f;
			tempConditionValue->currentDelayTime = 0.0f;
			tempConditionValue->maxCount = 1;
			tempConditionValue->curCount = 0;

			ProjectileStat* tempStat = new ProjectileStat();
			tempStat->damage = 11.0f;
			tempStat->stagger = 3.0f;
			tempStat->speed = 12.0f;
			tempStat->range = 0.0f;

			mInventory.arcanaDash->arcanaInfo = tempInfo;
			mInventory.arcanaDash->projectileStat = tempStat;
			mInventory.arcanaDash->conditionValue = tempConditionValue;
		}
		mInventory.arcanaSignature = new Arcana();
		{
			ArcanaInfo* tempInfo = new ArcanaInfo();
			tempInfo->name = eArcanaName::ExplodingFireball;
			tempInfo->category = eArcanaCategory::Range;
			tempInfo->type = eArcanaType::SignatureArcana;
			tempInfo->motion = ePlayerMotion::AOE;

			ProjectileConditionValue* tempConditionValue = new ProjectileConditionValue();
			tempConditionValue->cooldownReady = true;
			tempConditionValue->complete = false;
			tempConditionValue->cooldownTime = 0.6f;
			tempConditionValue->currentCooldownTime = 0.0f;
			tempConditionValue->delayTime = 0.0f;
			tempConditionValue->currentDelayTime = 0.0f;
			tempConditionValue->maxCount = 1;
			tempConditionValue->curCount = 0;

			ProjectileStat* tempStat = new ProjectileStat();
			tempStat->damage = 11.0f;
			tempStat->stagger = 3.0f;
			tempStat->speed = 0.0f;
			tempStat->range = 0.0f;

			mInventory.arcanaSignature->arcanaInfo = tempInfo;
			mInventory.arcanaSignature->projectileStat = tempStat;
			mInventory.arcanaSignature->conditionValue = tempConditionValue;
		}
		mInventory.arcanaStandardA = new Arcana();
		{
			ArcanaInfo* tempInfo = new ArcanaInfo();
			tempInfo->name = eArcanaName::DragonArc;
			tempInfo->category = eArcanaCategory::Range;
			tempInfo->type = eArcanaType::StandardArcana;
			tempInfo->motion = ePlayerMotion::Basic;

			ProjectileConditionValue* tempConditionValue = new ProjectileConditionValue();
			tempConditionValue->cooldownReady = true;
			tempConditionValue->complete = false;
			tempConditionValue->cooldownTime = 2.5f;
			tempConditionValue->currentCooldownTime = 0.0f;
			tempConditionValue->delayTime = 0.07f;
			tempConditionValue->currentDelayTime = 0.0f;
			tempConditionValue->maxCount = 6;
			tempConditionValue->curCount = 0;
					
			ProjectileStat* tempStat = new ProjectileStat();
			tempStat->damage = 11.0f;
			tempStat->stagger = 3.0f;
			tempStat->speed = 12.75f;
			tempStat->range = 8.2f;

			mInventory.arcanaStandardA->arcanaInfo = tempInfo;
			mInventory.arcanaStandardA->projectileStat = tempStat;
			mInventory.arcanaStandardA->conditionValue = tempConditionValue;
		}
		mInventory.arcanaStandardB = new Arcana();
		{
			ArcanaInfo* tempInfo = new ArcanaInfo();
			ProjectileConditionValue* tempConditionValue = new ProjectileConditionValue();
			ProjectileStat* tempStat = new ProjectileStat();

			mInventory.arcanaStandardB->arcanaInfo = tempInfo;
			mInventory.arcanaStandardB->projectileStat = tempStat;
			mInventory.arcanaStandardB->conditionValue = tempConditionValue;
		}
		mInventory.arcanaStandardC = new Arcana();
		{
			ArcanaInfo* tempInfo = new ArcanaInfo();
			ProjectileConditionValue* tempConditionValue = new ProjectileConditionValue();
			ProjectileStat* tempStat = new ProjectileStat();

			mInventory.arcanaStandardC->arcanaInfo = tempInfo;
			mInventory.arcanaStandardC->projectileStat = tempStat;
			mInventory.arcanaStandardC->conditionValue = tempConditionValue;
		}
		mInventory.arcanaStandardD = new Arcana();
		{
			ArcanaInfo* tempInfo = new ArcanaInfo();
			ProjectileConditionValue* tempConditionValue = new ProjectileConditionValue();
			ProjectileStat* tempStat = new ProjectileStat();

			mInventory.arcanaStandardD->arcanaInfo = tempInfo;
			mInventory.arcanaStandardD->projectileStat = tempStat;
			mInventory.arcanaStandardD->conditionValue = tempConditionValue;
		}		
	}

#pragma endregion
	void PlayerScript::Update()
	{
		CreatureScript::Update();
		calculateMouseDirection();
		calculatePlayerDirection();
		switch (mPlayerState)
		{
		case js::PlayerScript::ePlayerState::IDLE:
		{
			Idle();
		}
		break;
		case js::PlayerScript::ePlayerState::MOVE:
		{
			Move();
		}
		break;
		case js::PlayerScript::ePlayerState::LBTN:
		{
			LBtn();
		}
		break;
		case js::PlayerScript::ePlayerState::RBTN:
		{
			RBtn();
		}
		break;
		case js::PlayerScript::ePlayerState::SPACE:
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
		skillProcess();
		physicalProcess();
	}
	void PlayerScript::Render()
	{
	}
#pragma region �浹 �� �̺�Ʈ
	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		FindTargetType(collider);		
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
		if (false == mArcanaUsing)
		{
			if (Input::GetKey(eKeyCode::S))
			{
				// ���� ��ȯ
				changePlayerDirection(eAxisValue::Down, true, false);
				// ���� �ٲٱ�
				changeState(ePlayerState::MOVE);
				// �ִϸ��̼� ���	
				playAnimation();
			}
			if (Input::GetKey(eKeyCode::D))
			{
				// ���� ��ȯ
				changePlayerDirection(eAxisValue::Up, false, false);
				// ���� �ٲٱ�
				changeState(ePlayerState::MOVE);
				// �ִϸ��̼� ���	
				playAnimation();
			}
			if (Input::GetKey(eKeyCode::A))
			{
				// ���� ��ȯ
				changePlayerDirection(eAxisValue::Down, false, false);
				// ���� �ٲٱ�
				changeState(ePlayerState::MOVE);
				// �ִϸ��̼� ���	
				playAnimation();
			}
			if (Input::GetKey(eKeyCode::W))
			{
				// ���� ��ȯ
				changePlayerDirection(eAxisValue::Up, true, false);
				// ���� �ٲٱ�
				changeState(ePlayerState::MOVE);
				// �ִϸ��̼� ���	
				playAnimation();
			}

			if (Input::GetKey(eKeyCode::LBTN)
				&& true == mInventory.arcanaBasic->conditionValue->cooldownReady)
			{
				if (nullptr == mInventory.arcanaBasic->arcanaInfo)
					return;
				// ���� ��ȯ
				mArcanaStartAngle = calculateRotateAngle();
				calculateAnimationDirection(mArcanaStartAngle);
				// ���� �ٲٱ�
				mInventory.arcanaBasic->conditionValue->cooldownReady = false;
				mInventory.arcanaBasic->conditionValue->begin = true;
				mArcanaUsing = true;
				changeState(ePlayerState::LBTN);
				// �ִϸ��̼� ���	
				playAnimation();
			}
			if (Input::GetKey(eKeyCode::RBTN)
				&& true == mInventory.arcanaStandardA->conditionValue->cooldownReady)
			{
				if (nullptr == mInventory.arcanaStandardA->arcanaInfo)
					return;
				// ���� ��ȯ
				mArcanaStartAngle = calculateRotateAngle();
				calculateAnimationDirection(mArcanaStartAngle);
				// ���� �ٲٱ�
				mInventory.arcanaStandardA->conditionValue->cooldownReady = false;
				mInventory.arcanaStandardA->conditionValue->begin = true;
				mArcanaUsing = true;
				changeState(ePlayerState::RBTN);
				// �ִϸ��̼� ���
				playAnimation();
			}			
			if (Input::GetKey(eKeyCode::F)
				&& true == mInventory.arcanaStandardB->conditionValue->cooldownReady)
			{
				if (nullptr == mInventory.arcanaStandardB->arcanaInfo)
					return;
				// ���� ��ȯ
				mArcanaStartAngle = calculateRotateAngle();
				calculateAnimationDirection(mArcanaStartAngle);
				// ���� �ٲٱ�
				mInventory.arcanaStandardB->conditionValue->cooldownReady = false;
				mInventory.arcanaStandardB->conditionValue->begin = true;
				mArcanaUsing = true;
				changeState(ePlayerState::F);
				// �ִϸ��̼� ���	
				playAnimation();
			}
			if (Input::GetKey(eKeyCode::R)
				&& true == mInventory.arcanaStandardC->conditionValue->cooldownReady)
			{
				if (nullptr == mInventory.arcanaStandardC->arcanaInfo)
					return;
				// ���� ��ȯ
				mArcanaStartAngle = calculateRotateAngle();
				calculateAnimationDirection(mArcanaStartAngle);
				// ���� �ٲٱ�
				mInventory.arcanaStandardC->conditionValue->cooldownReady = false;
				mInventory.arcanaStandardC->conditionValue->begin = true;
				mArcanaUsing = true;
				changeState(ePlayerState::R);
				// �ִϸ��̼� ���	
				playAnimation();
			}
			if (Input::GetKey(eKeyCode::Q)
				&& true == mInventory.arcanaSignature->conditionValue->cooldownReady)
			{
				if (nullptr == mInventory.arcanaSignature->arcanaInfo)
					return;
				// ���� ��ȯ
				mArcanaStartAngle = calculateRotateAngle();
				calculateAnimationDirection(mArcanaStartAngle);
				// ���� �ٲٱ�
				mInventory.arcanaSignature->conditionValue->cooldownReady = false;
				mInventory.arcanaSignature->conditionValue->begin = true;
				mArcanaUsing = true;
				changeState(ePlayerState::Q);
				// �ִϸ��̼� ���	
				playAnimation();
			}
		}
		if (Input::GetKey(eKeyCode::SPACE))
		{
			// ���� �ٲٱ�
			mInventory.arcanaDash->conditionValue->cooldownReady = false;
			mInventory.arcanaDash->conditionValue->begin = true;
			changeState(ePlayerState::SPACE);
			// �ִϸ��̼� ���	
			playAnimation();
		}
		
	}
	void PlayerScript::Move()
	{
		// �̵� ����
		if (false == mArcanaUsing)
		{
			if (Input::GetKey(eKeyCode::S))
			{
				Vector3 pos = mTransform->GetPosition();
				if (true == mSprintReady)
					pos += -mTransform->Up() * mSprintSpeed * Time::DeltaTime();
				else
					pos += -mTransform->Up() * mHealthStat.moveSpeed * Time::DeltaTime();

				mTransform->SetPosition(pos);
				changePlayerDirection(eAxisValue::Down, true, false);
			}
			if (Input::GetKey(eKeyCode::D))
			{
				Vector3 pos = mTransform->GetPosition();
				if (true == mSprintReady)
					pos += mTransform->Right() * mSprintSpeed * Time::DeltaTime();
				else
				pos += mTransform->Right() * mHealthStat.moveSpeed * Time::DeltaTime();
				mTransform->SetPosition(pos);
				changePlayerDirection(eAxisValue::Up, false, false);
			}
			if (Input::GetKey(eKeyCode::A))
			{
				Vector3 pos = mTransform->GetPosition();
				if (true == mSprintReady)
					pos += -mTransform->Right() * mSprintSpeed * Time::DeltaTime();
				else
					pos += -mTransform->Right() * mHealthStat.moveSpeed * Time::DeltaTime();
				
				mTransform->SetPosition(pos);
				changePlayerDirection(eAxisValue::Down, false, false);
			}
			if (Input::GetKey(eKeyCode::W))
			{
				Vector3 pos = mTransform->GetPosition();
				if (true == mSprintReady)
					pos += mTransform->Up() * mSprintSpeed * Time::DeltaTime();
				else
					pos += mTransform->Up() * mHealthStat.moveSpeed * Time::DeltaTime();
				
				mTransform->SetPosition(pos);
				changePlayerDirection(eAxisValue::Up, true, false);
			}

			// ������ȯ + �ִϸ��̼� ����
			if (Input::GetKeyDown(eKeyCode::S))
			{
				changePlayerDirection(eAxisValue::Down, true, true);
				playAnimation();
			}
			if (Input::GetKeyDown(eKeyCode::D))
			{
				changePlayerDirection(eAxisValue::Up, false, true);
				playAnimation();
			}
			if (Input::GetKeyDown(eKeyCode::A))
			{
				changePlayerDirection(eAxisValue::Down, false, true);
				playAnimation();
			}
			if (Input::GetKeyDown(eKeyCode::W))
			{
				changePlayerDirection(eAxisValue::Up, true, true);
				playAnimation();
			}

			if (Input::GetKey(eKeyCode::LBTN)
				&& true == mInventory.arcanaBasic->conditionValue->cooldownReady)
			{
				if (nullptr == mInventory.arcanaBasic->arcanaInfo)
					return;
				// ���� ��ȯ
				mArcanaStartAngle = calculateRotateAngle();
				calculateAnimationDirection(mArcanaStartAngle);
				// ���� �ٲٱ�
				mInventory.arcanaBasic->conditionValue->cooldownReady = false;
				mInventory.arcanaBasic->conditionValue->begin = true;
				mArcanaUsing = true;
				changeState(ePlayerState::LBTN);
				// �ִϸ��̼� ���	
				playAnimation();
			}
			if (Input::GetKey(eKeyCode::RBTN)
				&& true == mInventory.arcanaStandardA->conditionValue->cooldownReady)
			{
				if (nullptr == mInventory.arcanaStandardA->arcanaInfo)
					return;
				// ���� ��ȯ
				mArcanaStartAngle = calculateRotateAngle();
				calculateAnimationDirection(mArcanaStartAngle);
				// ���� �ٲٱ�
				mInventory.arcanaStandardA->conditionValue->cooldownReady = false;
				mInventory.arcanaStandardA->conditionValue->begin = true;
				mArcanaUsing = true;
				changeState(ePlayerState::RBTN);
				// �ִϸ��̼� ���	
				playAnimation();
			}
			if (Input::GetKey(eKeyCode::F)
				&& true == mInventory.arcanaStandardB->conditionValue->cooldownReady)
		{
			if (nullptr == mInventory.arcanaStandardB->arcanaInfo)
				return;
			// ���� ��ȯ
			mArcanaStartAngle = calculateRotateAngle();
			calculateAnimationDirection(mArcanaStartAngle);
			// ���� �ٲٱ�
			mInventory.arcanaStandardB->conditionValue->cooldownReady = false;
			mInventory.arcanaStandardB->conditionValue->begin = true;
			mArcanaUsing = true;
			changeState(ePlayerState::F);
			// �ִϸ��̼� ���	
			playAnimation();
		}
			if (Input::GetKey(eKeyCode::R)
				&& true == mInventory.arcanaStandardC->conditionValue->cooldownReady)
		{
			if (nullptr == mInventory.arcanaStandardC->arcanaInfo)
				return;
			// ���� ��ȯ
			mArcanaStartAngle = calculateRotateAngle();
			calculateAnimationDirection(mArcanaStartAngle);
			// ���� �ٲٱ�
			mInventory.arcanaStandardC->conditionValue->cooldownReady = false;
			mInventory.arcanaStandardC->conditionValue->begin = true;
			mArcanaUsing = true;
			changeState(ePlayerState::R);
			// �ִϸ��̼� ���	
			playAnimation();
		}
			if (Input::GetKey(eKeyCode::Q)
				&& true == mInventory.arcanaSignature->conditionValue->cooldownReady)
		{
			if (nullptr == mInventory.arcanaSignature->arcanaInfo)
				return;
			// ���� ��ȯ
			mArcanaStartAngle = calculateRotateAngle();
			calculateAnimationDirection(mArcanaStartAngle);
			// ���� �ٲٱ�
			mInventory.arcanaSignature->conditionValue->cooldownReady = false;
			mInventory.arcanaSignature->conditionValue->begin = true;
			mArcanaUsing = true;
			changeState(ePlayerState::Q);
			// �ִϸ��̼� ���	
			playAnimation();
		}
		}

		// ���� ��ȯ
		if (Input::GetKeyUp(eKeyCode::S))
			changePlayerDirection(eAxisValue::Down, true, true);
		if (Input::GetKeyUp(eKeyCode::D))
			changePlayerDirection(eAxisValue::Up, false, true);
		if (Input::GetKeyUp(eKeyCode::A))
			changePlayerDirection(eAxisValue::Down, false, true);
		if (Input::GetKeyUp(eKeyCode::W))
			changePlayerDirection(eAxisValue::Up, true, true);

		
		if (Vector2::Zero == mCurrentDirection)
		{
			changeState(ePlayerState::IDLE);
			playAnimation();
		}

		if (Input::GetKey(eKeyCode::SPACE))
		{
			// ���� �ٲٱ�
		/*	mInventory.arcanaDash->conditionValue->cooldownReady = false;
			mInventory.arcanaDash->conditionValue->begin = true;*/
			changeState(ePlayerState::SPACE);
			// �ִϸ��̼� ���	
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

	void PlayerScript::physicalProcess()
	{
		if (ePlayerState::MOVE != mPlayerState)
		{
			mSprintReady = false;
			mSprintCheck = 0;
			return;
		}
		if (false == mSprintReady)
		{
			mSprintCheck += Time::DeltaTime();
			if (mSprintCheck >= mSprintTime)
			{
				mSprintReady = true;
				mSprintSpeed = mHealthStat.moveSpeed * 1.4f;
			}			
		}		
	}

	void PlayerScript::skillProcess()
	{
		skillCooldown();
		skillExcute();
	}

	void PlayerScript::skillCooldown()
	{
		if (nullptr != mInventory.arcanaBasic)
		{
			CooldownCheck(mInventory.arcanaBasic);
		}
		if (nullptr != mInventory.arcanaDash)
		{
			CooldownCheck(mInventory.arcanaDash);
		}
		if (nullptr != mInventory.arcanaSignature)
		{
			CooldownCheck(mInventory.arcanaSignature);
		}
		if (nullptr != mInventory.arcanaStandardA)
		{
			CooldownCheck(mInventory.arcanaStandardA);
		}
		if (nullptr != mInventory.arcanaStandardB)
		{
			CooldownCheck(mInventory.arcanaStandardB);
		}
		if (nullptr != mInventory.arcanaStandardC)
		{
			CooldownCheck(mInventory.arcanaStandardC);
		}
	}
	void PlayerScript::CooldownCheck(Arcana* target)
	{
		// ��ٿ� �Ϸ���°� �ƴ϶��
		if (false == target->conditionValue->cooldownReady)
		{
			target->conditionValue->currentCooldownTime += Time::DeltaTime();
			if (target->conditionValue->currentCooldownTime >= target->conditionValue->cooldownTime)
			{
				target->conditionValue->cooldownReady = true;
				target->conditionValue->complete = false;
				target->conditionValue->currentCooldownTime = 0;
			}
		}
	}

	void PlayerScript::skillExcute()
	{
		if (true == mInventory.arcanaBasic->conditionValue->begin)
			arcanaCompleteCheck(mInventory.arcanaBasic);

		if (true == mInventory.arcanaStandardA->conditionValue->begin)
			arcanaCompleteCheck(mInventory.arcanaStandardA);

		if (true == mInventory.arcanaDash->conditionValue->begin)
			arcanaCompleteCheck(mInventory.arcanaDash);

		if (true == mInventory.arcanaSignature->conditionValue->begin)
			arcanaCompleteCheck(mInventory.arcanaSignature);

		if (true == mInventory.arcanaStandardB->conditionValue->begin)
			arcanaCompleteCheck(mInventory.arcanaStandardB);

		if (true == mInventory.arcanaStandardC->conditionValue->begin)
			arcanaCompleteCheck(mInventory.arcanaStandardC);
	}
	bool PlayerScript::delayCheck(Arcana* target)
	{
		if (true == target->conditionValue->complete)
			return true;

		else
		{
			target->conditionValue->currentDelayTime += Time::DeltaTime();
			if (target->conditionValue->currentDelayTime >= target->conditionValue->delayTime)
				return true;
			else
				return false;
		}
	}
	bool PlayerScript::countCheck(Arcana* target)
	{
		// �ִ� ������ �ѱ��
		if (target->conditionValue->curCount >= target->conditionValue->maxCount)
		{
			target->conditionValue->curCount = 0;
			target->conditionValue->complete = true;
			target->conditionValue->cooldownReady = false;
			target->conditionValue->begin = false;
			mArcanaUsing = false;

			return false;
		}
		else
		{
			return true;
		}
	}
	void PlayerScript::arcanaCompleteCheck(Arcana* target)
	{
		// ��ų����� �Ϸ�Ȱ�� ret
		if (true == target->conditionValue->complete)
			return;
		
		if (true == countCheck(target))
		{
			if (true == delayCheck(target))
			{
				shoot(target);
				++target->conditionValue->curCount;
				target->conditionValue->currentDelayTime = 0.0f;
			}
		}
	}

	ArcanaScript* PlayerScript::redeployProjectiles(Arcana* target)
	{
		// ��ȿ�� ����ü ã��
		int index = findProjectilePool();

		// ���� ����		
		projectileRotates(mProjectiles[index], mArcanaStartAngle);
		if (0 >= mArcanaStartAngle && -3.14 <= mArcanaStartAngle)
			mIsProjectileRight = true;
		else
			mIsProjectileRight = false;
		// ��ġ ����
		if (eArcanaName::DragonArc == target->arcanaInfo->name)
		{
			// ȸ���� ����ü �������� cos pos.y �� ������ ��� �����ϱ�
			mProjectiles[index]->SetStartPos(mTransform->GetPosition());
		}
		else
		{
			mProjectiles[index]->SetStartPos(mTransform->GetPosition());
		}

		return mProjectiles[index];
	}
	void PlayerScript::shoot(Arcana* target)
	{
		redeployProjectiles(target)->ActiveArcana(target, mIsProjectileRight);
	}
	int PlayerScript::findProjectilePool()
	{
		for (int index = 0; index < PROJECTILE_POOL; ++index)
		{
			// ������ ��������
			if (nullptr == mProjectiles[index])
				continue;
			// ������̸� ��������
			/*if (eProjectileState::Disabled == mProjectiles[index]->IsActiveProjectile())
			{
				return index;
			}*/
			if (false == mProjectiles[index]->GetProjectileAbled())
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
	void PlayerScript::dashForce()
	{
		// �������¶�� ĳ���� ����, �̵����̸� �̵��������� ���
		if (Vector2::Zero == mCurrentDirection)
		{
			mRigidbody->SetVelocity(mAnimationDirection* 70.0f);
		}
		else
		{
			mRigidbody->SetVelocity(mCurrentDirection * 70.0f);
		}		
	}
	
	void PlayerScript::calculateMouseDirection()
	{
		// ���콺 ���� ���ϱ�
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
		float x = 0;
		float y = 0;

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
	void PlayerScript::calculateAnimationDirection(float angle)
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

	void PlayerScript::changePlayerDirection(eAxisValue direction, bool isYAxis, bool isKeyUp)
	{
		// AnimationDirection�� �����ϰ�, XDir, YDir ���� ������
		if (isYAxis)
		{
			if (eAxisValue::Up == direction)
				mAnimationDirection = Vector2(0, 1);
			if (eAxisValue::Down == direction)
				mAnimationDirection = Vector2(0, -1);

			// Y���� 0�� �ƴϰ�, �Էµ� ���� ���� ���� �ݴ��ΰ�� = �������°� �ƴ� ��Ȳ���� W�� S�� ���� �������
			if (direction != mYDir && eAxisValue::None != mYDir)
				mYDir = eAxisValue::None;
			else
				mYDir = direction;

			if (true == isKeyUp)
				mYDir = eAxisValue::None;
		}
		else
		{
			if (eAxisValue::Up == direction)
				mAnimationDirection = Vector2(1, 0);
			if (eAxisValue::Down == direction)
				mAnimationDirection = Vector2(-1, 0);

			// ���� ���� ������ �ݴ�Ű�� ������ 0�� �Ǿ����!
			if (direction != mXDir && eAxisValue::None != mXDir)
				mXDir = eAxisValue::None;
			else
				mXDir = direction;

			// ������ �ִµ� Ű�� ���� ����� �ϴ� ���
			if (true == isKeyUp)
				mXDir = eAxisValue::None;
		}
	}

	void PlayerScript::changeState(ePlayerState changeState)
	{
		mPlayerState = changeState;
	}	

#pragma region �ִϸ��̼� �����Լ�
	void PlayerScript::playAnimation()
	{
		switch (mPlayerState)
		{
		case js::PlayerScript::ePlayerState::IDLE:
		{
			playIdleAnimation();
		}
		break;
		case js::PlayerScript::ePlayerState::MOVE:
		{
			playMoveAnimation();
		}
		break;
		case js::PlayerScript::ePlayerState::LBTN:
		{
			findAnimation(mInventory.arcanaBasic->arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::RBTN:
		{
			findAnimation(mInventory.arcanaStandardA->arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::SPACE:
		{
			playDashAnimation();
		}
		break;
		case js::PlayerScript::ePlayerState::Q:
		{
			findAnimation(mInventory.arcanaSignature->arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::F:
		{
			findAnimation(mInventory.arcanaStandardB->arcanaInfo->motion);
		}
		break;
		case js::PlayerScript::ePlayerState::R:
		{
			findAnimation(mInventory.arcanaStandardC->arcanaInfo->motion);
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
}