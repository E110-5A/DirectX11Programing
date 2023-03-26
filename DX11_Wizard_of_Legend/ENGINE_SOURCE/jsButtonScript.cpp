#include "jsButtonScript.h"
#include "jsInput.h"
#include "jsGameObject.h"
#include "jsTransform.h"
#include "jsMeshRenderer.h"

namespace js
{
	Button::Button()
	{
	}
	Button::~Button()
	{
	}
	void Button::Initialize()
	{
	}
	void Button::Update()
	{
		// 마우스 위치
		Vector3 mousePos = Input::GetMouseWorldPosition();

		// 내 위치
		Transform* myTransform = GetOwner()->GetComponent<Transform>();
		Vector3 myPosition = myTransform->GetPosition();

		// 이미지 크기
		BaseRenderer* myRenderer = GetOwner()->GetComponent<BaseRenderer>();
		std::shared_ptr<Texture> myTexture = myRenderer->GetMaterial()->GetTexture();

		Vector3 textSize = Vector3((float)myTexture->GetWidth(), (float)myTexture->GetHeight(), 1.0f);

		if (myPosition.x <= mousePos.x && mousePos.x < myPosition.x + textSize.x
			&& myPosition.y <= mousePos.y && mousePos.y < myPosition.y + textSize.y)
			mIsMouseOn = true;
		else
			mIsMouseOn = false;

		if (Input::GetKeyDown(eKeyCode::LBTN) && mIsMouseOn)
			Action();
	}
	void Button::FixedUpdate()
	{
	}
	void Button::Render()
	{
	}
	void Button::Action()
	{
		int a = 0;
	}
}
