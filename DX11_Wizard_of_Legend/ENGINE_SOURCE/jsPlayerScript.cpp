#include "jsPlayerScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"
#include "jsAnimator.h"
#include "jsResources.h"

namespace js
{
	PlayerScript::PlayerScript()
		: Script()
		, movespeed(3.0f)
		, mDir(Vector2::Zero)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		CreateAnimation();
		
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
		}
		/*Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Up() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
			animator->Play(L"PlayerRunDown");
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Right() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
			animator->Play(L"PlayerRunRight");

		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Right() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
			animator->Play(L"PlayerRunLeft");
		}		
		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Up() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
			animator->Play(L"PlayerRunUp");
		}*/

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

		animator->Create(L"PlayerRunDown",	texture, Vector2(0.0f,	49.0f), defaultSize, Vector2::Zero, 8, 0.1f);
		animator->Create(L"PlayerRunRight", texture, Vector2(48.0f, 97.0f), defaultSize, Vector2::Zero, 8, 0.1f);
		animator->Create(L"PlayerRunLeft",	texture, Vector2(96.0f, 145.0f), defaultSize, Vector2::Zero, 8, 0.1f);
		animator->Create(L"PlayerRunUp",	texture, Vector2(144.0f, 193.0f), defaultSize, Vector2::Zero, 8, 0.1f);

		animator->Create(L"PlayerDashRight",	texture, Vector2(0.0f, 242.0f), defaultSize, Vector2::Zero, 6, 0.1f);
		animator->Create(L"PlayerDashLeft",		texture, Vector2(48.0f, 290.0f), defaultSize, Vector2::Zero, 6, 0.1f);

		animator->Create(L"PlayerBackhandDown",		texture, Vector2(0.0f, 339.0f), defaultSize, Vector2::Zero, 9, 0.1f);
		animator->Create(L"PlayerBackhandRight",	texture, Vector2(48.0f, 387.0f), defaultSize, Vector2::Zero, 9, 0.1f);
		animator->Create(L"PlayerBackhandLeft",		texture, Vector2(96.0f, 435.0f), defaultSize, Vector2::Zero, 9, 0.1f);
		animator->Create(L"PlayerBackhandUp",		texture, Vector2(144.0f, 483.0f), defaultSize, Vector2::Zero, 9, 0.1f);

		animator->Create(L"PlayerForehandDown",		texture, Vector2(0.0f, 532.0f), defaultSize, Vector2::Zero, 9, 0.1f);
		animator->Create(L"PlayerForehandRight",	texture, Vector2(48.0f, 580.0f), defaultSize, Vector2::Zero, 8, 0.1f);
		animator->Create(L"PlayerForehandLeft",		texture, Vector2(96.0f, 628.0f), defaultSize, Vector2::Zero, 8, 0.1f);
		animator->Create(L"PlayerForehandUp",		texture, Vector2(144.0f, 676.0f), defaultSize, Vector2::Zero, 12, 0.1f);

		animator->Create(L"PlayerGroundSlamDown",	texture, Vector2(0.0f, 725.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		animator->Create(L"PlayerGroundSlamUp",		texture, Vector2(48.0f, 773.0f), defaultSize, Vector2::Zero, 10, 0.1f);



		//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		//animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		//animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		//animator->GetActionEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
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

	void PlayerScript::Idle()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::DOWN))
		{			
			animator->Play(L"PlayerRunDown");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			animator->Play(L"PlayerRunRight");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			animator->Play(L"PlayerRunLeft");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			animator->Play(L"PlayerRunUp");
			mState = eState::Move;
		}
	}

	void PlayerScript::Move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		
		// 이동 로직
		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Up() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Right() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Right() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Up() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{			
			animator->Play(L"PlayerIdleDown");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{			
			animator->Play(L"PlayerIdleRight");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{			
			animator->Play(L"PlayerIdleLeft");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::UP))
		{			
			animator->Play(L"PlayerIdleUp");
			mState = eState::Idle;
		}
	}

}