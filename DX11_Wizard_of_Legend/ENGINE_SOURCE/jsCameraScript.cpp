#include "jsCameraScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"

namespace js
{
	CameraScript::CameraScript()
		: Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initialize()
	{
	}

	void CameraScript::Update()
	{
		FollowTarget();
		/*Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
			pos += 30.0f * tr->Right() * Time::DeltaTime();

		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
			pos += 30.0f * -tr->Right() * Time::DeltaTime();

		else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
			pos += 30.0f * tr->Up() * Time::DeltaTime();

		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
			pos += 30.0f * -tr->Up() * Time::DeltaTime();

		else if (Input::GetKeyState(eKeyCode::NUM_1) == eKeyState::PRESSED)
			pos += 30.0f * tr->Foward() * Time::DeltaTime();

		else if (Input::GetKeyState(eKeyCode::NUM_2) == eKeyState::PRESSED)
			pos += 30.0f * -tr->Foward() * Time::DeltaTime();


		tr->SetPosition(pos);*/
	}
	void CameraScript::Render()
	{
	}
	void CameraScript::FollowTarget()
	{
		if (nullptr == mFollowTarget)
			return;
		if (GameObject::Active != mFollowTarget->GetState())
			return;

		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Transform* targetTr = mFollowTarget->GetComponent<Transform>();
		Vector3 targetPosition = targetTr->GetPosition();

		myTr->SetPosition(targetPosition);
	}
}