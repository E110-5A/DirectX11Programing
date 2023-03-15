#include "jsPlayerScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"
#include "jsAnimator.h"

namespace js
{
	PlayerScript::PlayerScript()
		: Script()
		, movespeed(3.0f)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		animator->GetActionEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
				
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

		if (Input::GetKey(eKeyCode::DOWN))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Up() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Up() * movespeed * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::N_1))
		{
			animator->Play(L"MoveDown");
		}
	}

	void PlayerScript::Render()
	{
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

}