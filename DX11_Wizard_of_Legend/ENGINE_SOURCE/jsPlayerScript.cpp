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
		, mProjectile(nullptr)
		, mProjectileType(eArcanaCategory::Melee)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		createAnimation();
		addEvent();
	}

	void PlayerScript::Update()
	{
		if (mState == eState::AA)
			int a = 0;
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
	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::createAnimation()
	{
		// 애니메이터 가져옴
		Animator* animator = GetOwner()->GetComponent<Animator>();

		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		// 리소스 가져와서 생성
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PlayerSpriteSheet", L"Player\\PlayerSpriteSheet.png");

		animator->Create(L"PlayerIdleDown", texture, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerIdleRight", texture, Vector2(48.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerIdleLeft", texture, Vector2(96.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerIdleUp", texture, Vector2(144.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);

		animator->Create(L"PlayerRunDown", texture, Vector2(0.0f, 49.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerRunRight", texture, Vector2(0.0f, 97.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerRunLeft", texture, Vector2(0.0f, 145.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerRunUp", texture, Vector2(0.0f, 193.0f), defaultSize, Vector2::Zero, 10, 0.1f);

		animator->Create(L"PlayerDashDown", texture, Vector2(0.0f, 242.0f), defaultSize, Vector2::Zero, 4, 0.1f);
		animator->Create(L"PlayerDashRight", texture, Vector2(0.0f, 290.0f), defaultSize, Vector2::Zero, 6, 0.1f);
		animator->Create(L"PlayerDashLeft", texture, Vector2(0.0f, 338.0f), defaultSize, Vector2::Zero, 6, 0.1f);
		animator->Create(L"PlayerDashUp", texture, Vector2(0.0f, 386.0f), defaultSize, Vector2::Zero, 5, 0.1f);

		animator->Create(L"PlayerAABDown", texture, Vector2(0.0f, 435.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerAABRight", texture, Vector2(0.0f, 483.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerAABLeft", texture, Vector2(0.0f, 531.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerAABUp", texture, Vector2(0.0f, 579.0f), defaultSize, Vector2::Zero, 9, 0.075f);

		animator->Create(L"PlayerAAFDown", texture, Vector2(0.0f, 628.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerAAFRight", texture, Vector2(0.0f, 676.0f), defaultSize, Vector2::Zero, 8, 0.075f);
		animator->Create(L"PlayerAAFLeft", texture, Vector2(0.0f, 772.0f), defaultSize, Vector2::Zero, 8, 0.075f);
		animator->Create(L"PlayerAAFUp", texture, Vector2(0.0f, 772.0f), defaultSize, Vector2::Zero, 12, 0.075f);

		animator->Create(L"PlayerBackhandDown", texture, Vector2(0.0f, 435.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerBackhandRight", texture, Vector2(0.0f, 483.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerBackhandLeft", texture, Vector2(0.0f, 531.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerBackhandUp", texture, Vector2(0.0f, 579.0f), defaultSize, Vector2::Zero, 9, 0.075f);

		animator->Create(L"PlayerForehandDown", texture, Vector2(0.0f, 628.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerForehandRight", texture, Vector2(0.0f, 676.0f), defaultSize, Vector2::Zero, 8, 0.075f);
		animator->Create(L"PlayerForehandLeft", texture, Vector2(0.0f, 724.0f), defaultSize, Vector2::Zero, 8, 0.075f);
		animator->Create(L"PlayerForehandUp", texture, Vector2(0.0f, 772.0f), defaultSize, Vector2::Zero, 12, 0.075f);

		animator->Create(L"PlayerGroundSlamDown", texture, Vector2(0.0f, 821.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerGroundSlamUp", texture, Vector2(0.0f, 869.0f), defaultSize, Vector2::Zero, 10, 0.1f);

		animator->Create(L"PlayerAOEDown", texture, Vector2(0.0f, 918.0f), defaultSize, Vector2::Zero, 9, 0.1f);
		animator->Create(L"PlayerAOERight", texture, Vector2(0.0f, 966.0f), defaultSize, Vector2::Zero, 12, 0.1f);
		animator->Create(L"PlayerAOELeft", texture, Vector2(0.0f, 1014.0f), defaultSize, Vector2::Zero, 12, 0.1f);
		animator->Create(L"PlayerAOEUp", texture, Vector2(0.0f, 1062.0f), defaultSize, Vector2::Zero, 11, 0.1f);

		animator->Create(L"PlayerHurtDown", texture, Vector2(0.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerHurtRight", texture, Vector2(48.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerHurtLeft", texture, Vector2(96.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerHurtUp", texture, Vector2(144.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);

		animator->Create(L"PlayerKickDown", texture, Vector2(0.0f, 1159.0f), defaultSize, Vector2::Zero, 11, 0.1f);
		animator->Create(L"PlayerKickLeft", texture, Vector2(0.0f, 1255.0f), defaultSize, Vector2::Zero, 9, 0.1f);
		animator->Create(L"PlayerKickRight", texture, Vector2(0.0f, 1207.0f), defaultSize, Vector2::Zero, 9, 0.1f);
		animator->Create(L"PlayerKickUp", texture, Vector2(0.0f, 1303.0f), defaultSize, Vector2::Zero, 8, 0.1f);



		animator->Play(L"PlayerIdleDown");
	}
	void PlayerScript::addEvent()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		//animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		//animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		//animator->GetActionEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);



		// AA, Basic
		animator->GetStartEvent(L"PlayerAABDown") = std::bind(&PlayerScript::shoot, this);
		animator->GetStartEvent(L"PlayerAABRight") = std::bind(&PlayerScript::shoot, this);
		animator->GetStartEvent(L"PlayerAABLeft") = std::bind(&PlayerScript::shoot, this);
		animator->GetStartEvent(L"PlayerAABUp") = std::bind(&PlayerScript::shoot, this);
		animator->GetStartEvent(L"PlayerAAFDown") = std::bind(&PlayerScript::shoot, this);
		animator->GetStartEvent(L"PlayerAAFRight") = std::bind(&PlayerScript::shoot, this);
		animator->GetStartEvent(L"PlayerAAFLeft") = std::bind(&PlayerScript::shoot, this);
		animator->GetStartEvent(L"PlayerAAFUp") = std::bind(&PlayerScript::shoot, this);

		animator->GetActionEvent(L"PlayerAABDown", 4) = std::bind(&PlayerScript::idleState, this);
		animator->GetActionEvent(L"PlayerAABRight", 4) = std::bind(&PlayerScript::idleState, this);
		animator->GetActionEvent(L"PlayerAABLeft", 4) = std::bind(&PlayerScript::idleState, this);
		animator->GetActionEvent(L"PlayerAABUp", 4) = std::bind(&PlayerScript::idleState, this);
		animator->GetActionEvent(L"PlayerAAFDown", 4) = std::bind(&PlayerScript::idleState, this);
		animator->GetActionEvent(L"PlayerAAFRight", 4) = std::bind(&PlayerScript::idleState, this);
		animator->GetActionEvent(L"PlayerAAFLeft", 4) = std::bind(&PlayerScript::idleState, this);
		animator->GetActionEvent(L"PlayerAAFUp", 4) = std::bind(&PlayerScript::idleState, this);

		animator->GetActionEvent(L"PlayerAABDown", 3) = std::bind(&PlayerScript::playerRush, this);
		animator->GetActionEvent(L"PlayerAABRight", 3) = std::bind(&PlayerScript::playerRush, this);
		animator->GetActionEvent(L"PlayerAABLeft", 3) = std::bind(&PlayerScript::playerRush, this);
		animator->GetActionEvent(L"PlayerAABUp", 3) = std::bind(&PlayerScript::playerRush, this);
		animator->GetActionEvent(L"PlayerAAFDown", 3) = std::bind(&PlayerScript::playerRush, this);
		animator->GetActionEvent(L"PlayerAAFRight", 3) = std::bind(&PlayerScript::playerRush, this);
		animator->GetActionEvent(L"PlayerAAFLeft", 3) = std::bind(&PlayerScript::playerRush, this);
		animator->GetActionEvent(L"PlayerAAFUp", 3) = std::bind(&PlayerScript::playerRush, this);

		animator->GetCompleteEvent(L"PlayerAABDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAABRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAABLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAABUp") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAAFDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAAFRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAAFLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAAFUp") = std::bind(&PlayerScript::RetIdle, this);

		// BackHand

		animator->GetActionEvent(L"PlayerBackhandDown", 2) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerBackhandRight", 2) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerBackhandLeft", 2) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerBackhandUp", 2) = std::bind(&PlayerScript::shoot, this);
		animator->GetCompleteEvent(L"PlayerBackhandDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerBackhandRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerBackhandLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerBackhandUp") = std::bind(&PlayerScript::RetIdle, this);


		// Skill
		animator->GetActionEvent(L"PlayerForehandDown", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerForehandRight", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerForehandLeft", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerForehandUp", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetCompleteEvent(L"PlayerForehandDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerForehandRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerForehandLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerForehandUp") = std::bind(&PlayerScript::RetIdle, this);

		// Dash
		animator->GetCompleteEvent(L"PlayerDashDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerDashRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerDashLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerDashUp") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetStartEvent(L"PlayerDashDown") = std::bind(&PlayerScript::AddForce, this);
		animator->GetStartEvent(L"PlayerDashRight") = std::bind(&PlayerScript::AddForce, this);
		animator->GetStartEvent(L"PlayerDashLeft") = std::bind(&PlayerScript::AddForce, this);
		animator->GetStartEvent(L"PlayerDashUp") = std::bind(&PlayerScript::AddForce, this);

		// GroundSlam
		animator->GetActionEvent(L"PlayerGroundSlamDown", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerGroundSlamUp", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetCompleteEvent(L"PlayerGroundSlamDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerGroundSlamUp") = std::bind(&PlayerScript::RetIdle, this);

		// AOE
		animator->GetActionEvent(L"PlayerAOEDown", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerAOERight", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerAOELeft", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerAOEUp", 3) = std::bind(&PlayerScript::shoot, this);
		animator->GetCompleteEvent(L"PlayerAOEDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAOERight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAOELeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerAOEUp") = std::bind(&PlayerScript::RetIdle, this);

		// Kick
		animator->GetActionEvent(L"PlayerKickDown", 4) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerKickLeft", 4) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerKickRight", 4) = std::bind(&PlayerScript::shoot, this);
		animator->GetActionEvent(L"PlayerKickUp", 4) = std::bind(&PlayerScript::shoot, this);
		animator->GetCompleteEvent(L"PlayerKickDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerKickLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerKickRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerKickUp") = std::bind(&PlayerScript::RetIdle, this);

	}

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

	void PlayerScript::RetIdle()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		mState = eState::Idle;
		if (Vector2(V2DOWN) == mMoveDir)
		{
			animator->Play(L"PlayerIdleDown");
		}
		if (Vector2(V2RIGHT) == mMoveDir)
		{
			animator->Play(L"PlayerIdleRight");
		}
		if (Vector2(V2LEFT) == mMoveDir)
		{
			animator->Play(L"PlayerIdleLeft");
		}
		if (Vector2(V2UP) == mMoveDir)
		{
			animator->Play(L"PlayerIdleUp");
		}
	}
	void PlayerScript::AddForce()
	{
		Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
		rigidbody->SetVelocity(mMoveDir * 40);
	}
	void PlayerScript::AutoAttack()
	{
		// 다음 이미지로 세팅


		// 초기화
		RetIdle();
	}

	void PlayerScript::Idle()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();

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

		if (Input::GetKey(eKeyCode::LBTN))
		{
			mProjectileType = eArcanaCategory::Melee;
			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerAABDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerAABRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerAABLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerAABUp");
			}
			mState = eState::AA;
		}
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{
			mProjectileType = eArcanaCategory::Projectile;

			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerKickDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerKickRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerKickLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerKickUp");
			}
			mState = eState::Skill;
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
			dashAction();
		if (Input::GetKeyDown(eKeyCode::F))
		{
			mProjectileType = eArcanaCategory::Projectile;

			if (1 == mMoveDir.y)
				animator->Play(L"PlayerGroundSlamUp", false);
			else
				animator->Play(L"PlayerGroundSlamDown", false);
			mState = eState::Special;
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			mProjectileType = eArcanaCategory::Projectile;
			mState = eState::Ultimate;

			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerAOEDown", false);
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerAOERight", false);
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerAOELeft", false);
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerAOEUp", false);
			}
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
			mMoveDir = Vector2(0, -1);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Right() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(1, 0);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Right() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(-1, 0);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Up() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(0, 1);
		}


		if (Input::GetKey(eKeyCode::LBTN))
		{
			mProjectileType = eArcanaCategory::Melee;

			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerAABDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerAABRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerAABLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerAABUp");
			}
			mState = eState::AA;
		}
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{
			mProjectileType = eArcanaCategory::Projectile;

			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerKickDown", false);
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerKickRight", false);
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerKickLeft", false);
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerKickUp", false);
			}
			mState = eState::Skill;
		}
		if (Input::GetKeyDown(eKeyCode::F))
		{
			mProjectileType = eArcanaCategory::Projectile;
			if (1 == mMoveDir.y)
				animator->Play(L"PlayerGroundSlamUp", false);
			else
				animator->Play(L"PlayerGroundSlamDown", false);
			mState = eState::Special;
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			mProjectileType = eArcanaCategory::Projectile;
			mState = eState::Ultimate;
			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerAOEDown", false);
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerAOERight", false);
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerAOELeft", false);
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerAOEUp", false);
			}
		}

		if (Input::GetKeyDown(eKeyCode::SPACE))
			dashAction();


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
		if (Input::GetKeyDown(eKeyCode::SPACE))
			dashAction();
	}

	void PlayerScript::Skill()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
			dashAction();
	}

	void PlayerScript::Dash()
	{

	}

	void PlayerScript::Special()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
			dashAction();
	}

	void PlayerScript::Ultimate()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
			dashAction();
	}

	void PlayerScript::dashAction()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Vector2(V2DOWN) == mMoveDir)
		{
			animator->Play(L"PlayerDashDown", false);
		}
		if (Vector2(V2RIGHT) == mMoveDir)
		{
			animator->Play(L"PlayerDashRight", false);
		}
		if (Vector2(V2LEFT) == mMoveDir)
		{
			animator->Play(L"PlayerDashLeft", false);
		}
		if (Vector2(V2UP) == mMoveDir)
		{
			animator->Play(L"PlayerDashUp", false);
		}
		mState = eState::Dash;
	}


	void PlayerScript::shoot()
	{
		if (!mProjectile)
			return;
		Vector3 myDir = calculateMouseDir();
		float angle = projectileRotate(myDir);
		playerRotate(angle);
		activeProjectile();

	}


	void PlayerScript::calculateProjectileDir()
	{
	}
	Vector3 PlayerScript::calculateMouseDir()
	{
		// 마우스 방향 구하기
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector3 myPosistion = myTr->GetPosition();
		Vector3 mousePosition = Input::GetMouseWorldPosition();
		mousePosition.z = 1.0f;
		Vector3 myDir = mousePosition - myPosistion;
		myDir.Normalize();
		return myDir;
	}
	float PlayerScript::projectileRotate(Vector3 dir)
	{
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		// 회전값 구하기
		float angle = atan2(dir.y, dir.x) - atan2(myTr->Up().y, myTr->Up().x);
		// 투사체 Tr가져와서 rotate 변경
		Transform* projectileTr = mProjectile->GetOwner()->GetComponent<Transform>();
		projectileTr->SetRotation(Vector3(0.0f, 0.0f, angle));

		return angle;
	}
	void PlayerScript::playerRotate(float angle)
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
	void PlayerScript::playerRush()
	{
		// 이동
		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		myRigidbody->SetVelocity(mMoveDir * 21.0f);
	}
	void PlayerScript::activeProjectile()
	{
		// 투사체를 내 위치로 옮기기
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Transform* projecTr = mProjectile->GetOwner()->GetComponent<Transform>();
		projecTr->SetPosition(tr->GetPosition());

		// 투사체 설정 초기화
		mProjectile->ActiveProjectile(mProjectileType);
	}
	void PlayerScript::idleState()
	{
		mState = eState::Idle;
	}
}