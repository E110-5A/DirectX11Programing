#pragma once
#include "CommonInclude.h"
#include "jsMath.h"
#include "jsRenderer.h"

namespace js
{
	enum class eKeyCode
	{
		//Alphabet
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L, 
		Z, X, C, V, B, N, M,
		
		//Special Key
		ENTER, ESC, LSHIFT, LALT, LCTRL,
		SPACE, LEFT, RIGHT, UP, DOWN,
		LBTN, RBTN,
		
		//Num Pad
		NUM_0, NUM_1, NUM_2,
		NUM_3, NUM_4, NUM_5,
		NUM_6, NUM_7, NUM_8,
		NUM_9,

		//Num Line
		N_0, N_1, N_2, N_3, N_4, N_5,
		N_6, N_7, N_8, N_9,
		
		END,
	};
	enum eKeyState
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
			eKeyCode  eType;
			eKeyState eState;
			bool	  bPressed;
		};

		static void Initialize();
		static void Update();

		static __forceinline eKeyState GetKeyState(eKeyCode keyCode) 
		{ 
			return mKeys[static_cast<UINT>(keyCode)].eState; 
		}

		static __forceinline math::Vector3 GetMousePosition() { return mMousePosition; }
		
		static void CalculateMouseMatrix();
		static Vector3& GetMouseWorldPosition() { return mMouseWorldPosition; }
		static Vector3& GetMouseUIPosition() { return mMouseUIPosition; }
	

		//GetKey()		키를 누르는 시간만큼 true를 반환
		//GetKeyDown()	키를 눌렀을 때, 딱 한번 true를 반환
		//GetKeyUp()	키를 누르다 땠을 때, 딱 한번 true를 반환

		static __forceinline bool GetKey(eKeyCode keyCode) { return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::PRESSED; }
		static __forceinline bool GetKeyDown(eKeyCode keyCode) { return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::DOWN; }
		static __forceinline bool GetKeyUp(eKeyCode keyCode) { return mKeys[static_cast<UINT>(keyCode)].eState == eKeyState::UP; }
		

	private:
		Input() = delete;
		~Input() = delete;

	private:
		static std::vector<Key> mKeys;

		// 스크린 좌표계
		static Vector3 mMousePosition;
		// 월드 좌표계
		static Vector3 mMouseWorldPosition;
		// UI 좌표
		static Vector3 mMouseUIPosition;
	};
}
