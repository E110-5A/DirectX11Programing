#include "jsPlayerScript.h"

#include "jsInput.h"
#include "jsTime.h"

#include "jsResources.h"

#include "jsGameObject.h"

#include "jsTransform.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"


// 방향
#define V2DOWN 0,-1
#define V2RIGHT 1,0
#define V2LEFT -1,0
#define V2UP 0,1

namespace js
{
	PlayerScript::PlayerScript()
		: Script()
		, mState(eState::Idle)
		, movespeed(3.0f)
		, mMoveDir(Vector2::Zero)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		CreateAnimation();
		AddEvent();
	}

	void PlayerScript::Update()
	{
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

	void PlayerScript::CreateAnimation()
	{
		// 애니메이터 가져옴
		Animator* animator = GetOwner()->GetComponent<Animator>();


		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		// 리소스 가져와서 생성
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"PlayerSpriteSheet");
		animator->Create(L"PlayerIdleDown", texture, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerIdleRight", texture, Vector2(48.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerIdleLeft", texture, Vector2(96.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		animator->Create(L"PlayerIdleUp", texture, Vector2(144.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);

		animator->Create(L"PlayerRunDown", texture, Vector2(0.0f, 49.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerRunRight", texture, Vector2(0.0f, 97.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerRunLeft", texture, Vector2(0.0f, 145.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerRunUp", texture, Vector2(0.0f, 193.0f), defaultSize, Vector2::Zero, 10, 0.1f);

		animator->Create(L"PlayerDashRight", texture, Vector2(0.0f, 242.0f), defaultSize, Vector2::Zero, 6, 0.1f);
		animator->Create(L"PlayerDashLeft", texture, Vector2(0.0f, 290.0f), defaultSize, Vector2::Zero, 6, 0.1f);

		animator->Create(L"PlayerBackhandDown", texture, Vector2(0.0f, 339.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerBackhandRight", texture, Vector2(0.0f, 387.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerBackhandLeft", texture, Vector2(0.0f, 435.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerBackhandUp", texture, Vector2(0.0f, 483.0f), defaultSize, Vector2::Zero, 9, 0.075f);

		animator->Create(L"PlayerForehandDown", texture, Vector2(0.0f, 532.0f), defaultSize, Vector2::Zero, 9, 0.075f);
		animator->Create(L"PlayerForehandRight", texture, Vector2(0.0f, 580.0f), defaultSize, Vector2::Zero, 8, 0.075f);
		animator->Create(L"PlayerForehandLeft", texture, Vector2(0.0f, 628.0f), defaultSize, Vector2::Zero, 8, 0.075f);
		animator->Create(L"PlayerForehandUp", texture, Vector2(0.0f, 676.0f), defaultSize, Vector2::Zero, 12, 0.075f);

		animator->Create(L"PlayerGroundSlamDown", texture, Vector2(0.0f, 725.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerGroundSlamUp", texture, Vector2(0.0f, 773.0f), defaultSize, Vector2::Zero, 10, 0.1f);
	}
	void PlayerScript::AddEvent()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		//animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		//animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		//animator->GetActionEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);

		// AA, Ultimate
		animator->GetActionEvent(L"PlayerBackhandDown", 5) = std::bind(&PlayerScript::RetIdle, this);
		animator->GetActionEvent(L"PlayerBackhandRight", 5) = std::bind(&PlayerScript::RetIdle, this);
		animator->GetActionEvent(L"PlayerBackhandLeft", 5) = std::bind(&PlayerScript::RetIdle, this);
		animator->GetActionEvent(L"PlayerBackhandUp", 5) = std::bind(&PlayerScript::RetIdle, this);

		animator->GetCompleteEvent(L"PlayerBackhandDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerBackhandRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerBackhandLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerBackhandUp") = std::bind(&PlayerScript::RetIdle, this);


		// Skill
		animator->GetCompleteEvent(L"PlayerForehandDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerForehandRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerForehandLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerForehandUp") = std::bind(&PlayerScript::RetIdle, this);

		// Dash
		animator->GetCompleteEvent(L"PlayerDashRight") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerDashLeft") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetStartEvent(L"PlayerDashRight") = std::bind(&PlayerScript::AddForce, this);
		animator->GetStartEvent(L"PlayerDashLeft") = std::bind(&PlayerScript::AddForce, this);

		// Special
		animator->GetCompleteEvent(L"PlayerGroundSlamDown") = std::bind(&PlayerScript::RetIdle, this);
		animator->GetCompleteEvent(L"PlayerGroundSlamUp") = std::bind(&PlayerScript::RetIdle, this);
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
		rigidbody->SetVelocity(mMoveDir * 55);
	}

	void PlayerScript::AutoAttack()
	{
		// 투사체 날리기

		// 상태 갱신
		mState = eState::Idle;
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
			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerBackhandDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerBackhandRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerBackhandLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerBackhandUp");
			}
			mState = eState::AA;
		}
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{
			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerForehandDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerForehandRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerForehandLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerForehandUp");
			}
			mState = eState::Skill;
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
			DashAction();
		if (Input::GetKeyDown(eKeyCode::F))
		{
			if (1 == mMoveDir.y)
				animator->Play(L"PlayerGroundSlamUp", false);
			else
				animator->Play(L"PlayerGroundSlamDown", false);
			mState = eState::Special;
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerForehandDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerForehandRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerForehandLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerForehandUp");
			}
			mState = eState::Ultimate;
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
			pos += -tr->Up() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(0, -1);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Right() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(1, 0);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Right() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(-1, 0);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Up() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(0, 1);
		}
		

		if (Input::GetKey(eKeyCode::LBTN))
		{
			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerBackhandDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerBackhandRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerBackhandLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerBackhandUp");
			}
			mState = eState::AA;
		}
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{
			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerForehandDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerForehandRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerForehandLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerForehandUp");
			}
			mState = eState::Skill;
		}
		if (Input::GetKeyDown(eKeyCode::F))
		{
			if (1 == mMoveDir.y)
				animator->Play(L"PlayerGroundSlamUp", false);
			else
				animator->Play(L"PlayerGroundSlamDown", false);
			mState = eState::Special;
		}
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			if (Vector2(V2DOWN) == mMoveDir)
			{
				animator->Play(L"PlayerForehandDown");
			}
			if (Vector2(V2RIGHT) == mMoveDir)
			{
				animator->Play(L"PlayerForehandRight");
			}
			if (Vector2(V2LEFT) == mMoveDir)
			{
				animator->Play(L"PlayerForehandLeft");
			}
			if (Vector2(V2UP) == mMoveDir)
			{
				animator->Play(L"PlayerForehandUp");
			}
			mState = eState::Ultimate;
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
			DashAction();
		

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
			DashAction();
	}

	void PlayerScript::Skill()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
			DashAction();
	}

	void PlayerScript::Dash()
	{

	}

	void PlayerScript::Special()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
			DashAction();
	}

	void PlayerScript::Ultimate()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
			DashAction();
	}

	void PlayerScript::DashAction()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		// 오른쪽
		if (1 == mMoveDir.x)
			animator->Play(L"PlayerDashRight", false);
		else
			animator->Play(L"PlayerDashLeft", false);
		mState = eState::Dash;		
	}
}