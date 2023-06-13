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
		// ���콺 �Է� ��� dx�� �°� �����Ұ�

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
		// �θ� Ŭ������ ������ �����س��� �θ� �����ϵ��� �ϸ� �ɵ�
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