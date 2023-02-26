#include "jsPlayerScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"

namespace js
{
	PlayerScript::PlayerScript()
		: Script()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initalize()
	{
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::R))
		{
			Vector3 rot = tr->GetRotation();
			rot.z += 10.0f * Time::DeltaTime();
			tr->SetRotation(rot);
		}
	}

	void PlayerScript::Render()
	{
	}

}