#pragma once
#include "jsEngine.h"
#include "jsMath.h"

using namespace js::math;

namespace js
{
	enum class eKeyCode
	{
		//Alphabet
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		//Special
		ENTER, ESC, LSHIFT, LART, LCTRL,
		SPACE, LEFT, RIGHT, UP, DOWN,
		LBTN, RBTN,

		//Num Pad
		NUM_0,
		NUM_1, NUM_2, NUM_3,
		NUM_4, NUM_5, NUM_6,
		NUM_7, NUM_8, NUM_9,

		//Num Line
		N_0, N_1, N_2, N_3, N_4, N_5, N_6, N_7, N_8, N_9,

		END,
	};
	enum class eKeyState
	{
		DOWN,
		PRESSED,
		UP,
		NONE,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode	eKeyCode;
			eKeyState	eKeyState;
			bool		bPressed;
		};

	public:
		static void Initialize();
		static void Update();

		static __forceinline eKeyState GetKeyState(eKeyCode keyCode)
		{
			return mKeys[static_cast<UINT>(keyCode)].eKeyState;
		}
		static __forceinline Vector2 GetMousePos()
		{
			return mMousePos;
		}

	private:
		Input() = delete;
		~Input() = delete;

	private:
		static std::vector<Key> mKeys;
		static Vector2	mMousePos;
	};
}