#include "jsButton.h"
#include "jsInput.h"

#include "jsSceneManager.h"

namespace js
{
	Button::Button(eUIType type)
		: UIBase(type)
	{
		mOnClick = std::bind(&Button::Click, this);
	}
	Button::~Button()
	{
	}
	void Button::OnInit()
	{
	}
	void Button::OnActive()
	{
		UIBase::OnActive();
	}
	void Button::OnInActive()
	{
		UIBase::OnInActive();
	}
	void Button::OnTick()
	{
		// 마우스 입력 기능 dx에 맞게 수정할것

		/*Pos mousePos = Input::GetMousePos();
		Size size = GetSize();

		if (mScreenPos.x <= mousePos.x && mousePos.x < mScreenPos.x + size.x
			&& mScreenPos.y <= mousePos.y && mousePos.y < mScreenPos.y + size.y)
			mIsMouseOn = true;
		else
			mIsMouseOn = false;


		if (KEY_DOWN(eKeyCode::LBTN) && mIsMouseOn)
			mOnClick();*/
	}

	void Button::OnRender(HDC hdc)
	{
		// 부모 클래스에 렌더링 구현해놓고 부모 참조하도록 하면 될듯
	}
	void Button::OnClear()
	{
	}
	void Button::Click()
	{
		switch (mFunc)
		{
		case eBtnType::GoToSelectScene:
		{
		}
		break;
		case eBtnType::GoToPlayScene:
		{
		}
		break;
		case eBtnType::GoToTitleScene:
		{
		}
		break;
		}
	}
	
}