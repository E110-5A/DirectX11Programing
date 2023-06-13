#pragma once
#include "jsEngine.h"
#include "jsUIBase.h"


namespace js
{
	/*
	*	플레이어의 조작에 영향을 받지 않음
	*	-전체 화면 UI
	*	-기본 UI
	*	-HUD 이미지와 정보만 있는 UI 
	*	-버튼
	*	여러가지 다른 UI들을 자식구조로 구성해서 같이 움직이는 하나의 큰 UI도 있음
	*/
	class UIManager
	{
	public:
		static void Initialize();
		static void OnLoad(eUIType type);
		static void Tick();
		static void Render(HDC hdc);
		static void OnComplete(UIBase* addUI);
		static void OnFail();
		static void Release();

		static void Push(eUIType type);
		static void Pop(eUIType type);

		template <typename T>
		static T* GetUIInstant(eUIType type)
		{
			return dynamic_cast<T*>(mUIs[type]);
		}

	private:
		static void TitleSceneUI();

		static void PlayerUI();
		static void MonsterUI();
		static void InGameUI();

	private:
		static std::unordered_map<eUIType, UIBase*> mUIs;
		static std::queue<eUIType>					mRequestUIQueue;
		static std::stack<UIBase*>					mUIBases;
		static UIBase*								mCurrentData;
	};
}