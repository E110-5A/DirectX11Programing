#include "jsInput.h"
#include "jsApplication.h"

extern js::Application application;

namespace js
{
	std::vector<Input::Key> Input::mKeys;
	Vector2	Input::mMousePos = Vector2::Zero;
	int ASCII[(UINT)eKeyCode::END] =
	{
		'Q','W','E','R','T','Y','U','I','O','P',
		'A','S','D','F','G','H','J','K','L',
		'Z','X','C','V','B','N','M',

		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		VK_NUMPAD0,
		VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3,
		VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6,
		VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,

		'0','1','2','3','4','5','6','7','8','9',
	};


	void Input::Initialize()
	{
		for (size_t idx = 0; idx < (UINT)eKeyCode::END; ++idx)
		{
			Key key = { (eKeyCode)idx, eKeyState::NONE, false };

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		if (GetFocus())
		{
			// 키보드
			for (size_t idx = 0; idx < (UINT)eKeyCode::END; ++idx)
			{
				// 키가 눌린 경우
				if (GetAsyncKeyState(ASCII[idx]) & 0x8000)
				{
					// 이전에 눌렸음
					if (mKeys[idx].bPressed)
						mKeys[idx].eKeyState = eKeyState::PRESSED;
					else
						mKeys[idx].eKeyState = eKeyState::DOWN;

					mKeys[idx].bPressed = true;
				}
				// 키가 눌리지 않은 경우
				else
				{
					// 이전에 눌렸음
					if (mKeys[idx].bPressed)
						mKeys[idx].eKeyState = eKeyState::UP;
					else
						mKeys[idx].eKeyState = eKeyState::NONE;

					mKeys[idx].bPressed = false;
				}
			}

			// 마우스
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(application.GetHwnd(), &mousePos);
			mMousePos.x = (float)mousePos.x;
			mMousePos.y = (float)mousePos.y;
		}
		else
		{
			for (UINT idx = 0; idx < (UINT)eKeyCode::END; ++idx)
			{
				if (eKeyState::DOWN == mKeys[idx].eKeyState
					|| eKeyState::PRESSED == mKeys[idx].eKeyState)
					mKeys[idx].eKeyState = eKeyState::UP;
				else if (eKeyState::UP == mKeys[idx].eKeyState)
					mKeys[idx].eKeyState = eKeyState::NONE;

				mKeys[idx].bPressed = false;
			}
		}
	}
}