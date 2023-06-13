#include "jsUIManager.h"

#include "jsPanel.h"
#include "jsButton.h"
#include "jsHUD.h"

namespace js
{
	std::unordered_map<eUIType, UIBase*> UIManager::mUIs;
	std::queue<eUIType> UIManager::mRequestUIQueue;
	std::stack<UIBase*> UIManager::mUIBases;
	UIBase* UIManager::mCurrentData = nullptr;

	void UIManager::Initialize()
	{
		// 여기서 UI 메모리를 할당하면 된다

		//	Title Scene
		TitleSceneUI();
		
		InGameUI();
	}

	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UIBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}
		OnComplete(iter->second);
	}
	void UIManager::Tick()
	{
		// UI tick 호출
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			if (nullptr != uiBase)
			{
				uiBase->Tick();
			}
			uiBases.pop();
		}


		// UI 로드 진행
		if (mRequestUIQueue.size() > 0)
		{
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUI);
		}
	}
	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIBases;
		std::stack<UIBase*> tempStack = mUIBases;

		// ui 스택 뒤집기
		while (!uiBases.empty())
		{
			UIBase* uiBase = uiBases.top();
			tempStack.push(uiBase);
			uiBases.pop();
		}

		// ui 메시지 순차적으로 재생
		while (!tempStack.empty())
		{
			UIBase* uiBase = tempStack.top();

			if (nullptr != uiBase)
				uiBase->Render(hdc);

			tempStack.pop();
		}
	}

	void UIManager::OnComplete(UIBase* addUI)
	{
		if (nullptr == addUI)
			return;
		addUI->Initialize();
		addUI->Active();
		addUI->Tick();

		if (addUI->GetisFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				
				if (uiBase->GetisFullScreen())
					uiBase->InActive();
			}
		}
		mUIBases.push(addUI);
	}
	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}
	void UIManager::Release()
	{
		for (auto ui : mUIs)
		{
			delete ui.second;
			ui.second = nullptr;
		}
	}

	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}
	void UIManager::Pop(eUIType type)
	{
		if (0 >= mUIBases.size())
			return;

		std::stack<UIBase*> tempStack;

		UIBase* uiBase = nullptr;

		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();
			uiBase->InActive();

			if (uiBase->GetType() == type)
			{
				if (uiBase->GetisFullScreen())
				{
					std::stack<UIBase*> uiBases = mUIBases;
					while (!uiBases.empty())
					{
						UIBase* uiBase = uiBases.top();
						uiBases.pop();

						if (uiBase->GetisFullScreen())
						{
							break;
						}
					}
				}
				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase); 
			}
		}
		while (tempStack.size())
		{
			uiBase = tempStack.top();
			tempStack.pop();

			mUIBases.push(uiBase);
		}
	}

	void UIManager::TitleSceneUI()
	{
		/*Button* selectBtn = new Button(eUIType::SelectBtn);
		mUIs.insert(std::make_pair(eUIType::SelectBtn, selectBtn));
		selectBtn->ImageLoad(L"SelectBtn", L"..\\Resources\\Image\\Button\\Title_Play.bmp");
		selectBtn->SetPos(Vector2(470.0f, 300.0f));
		selectBtn->SetFunc(eBtnType::GoToSelectScene);

		Button* optionBtn = new Button(eUIType::OptionBtn);
		mUIs.insert(std::make_pair(eUIType::OptionBtn, optionBtn));
		optionBtn->ImageLoad(L"OptionBtn", L"..\\Resources\\Image\\Button\\Title_Options.bmp");
		optionBtn->SetPos(Vector2(470.0f, 370.0f));
		optionBtn->SetFunc(eBtnType::GoToOption);

		Button* quitBtn = new Button(eUIType::QuitBtn);
		mUIs.insert(std::make_pair(eUIType::QuitBtn, quitBtn));
		quitBtn->ImageLoad(L"QuitBtn", L"..\\Resources\\Image\\Button\\Title_Quit.bmp");
		quitBtn->SetPos(Vector2(470.0f, 440.0f));
		quitBtn->SetFunc(eBtnType::GoToTitleScene);*/
	}
	void UIManager::PlayerUI()
	{
	}
	void UIManager::MonsterUI()
	{
	}
	void UIManager::InGameUI()
	{		
		// PlayerInfo
		/*Panel* playerInfoPanel = new Panel(eUIType::PlayerInfo);
		mUIs.insert(std::make_pair(eUIType::PlayerInfo, playerInfoPanel));
		playerInfoPanel->ImageLoad(L"PlayerInfoPanel", L"..\\Resources\\Image\\UI\\InGame\\PlayerInfoPanel.bmp");
		playerInfoPanel->SetPos(Vector2((Window_Width / 2) - 170, Window_Height - 128));

		BarUI* hpBar = new BarUI(eUIType::HpBar);
		mUIs.insert(std::make_pair(eUIType::HpBar, hpBar));
		hpBar->ImageLoad(L"HpBar", L"..\\Resources\\Image\\UI\\InGame\\HPBar.bmp");
		hpBar->SetPos(Vector2(10.0f, 74.0f));

		BarUI* expBar = new BarUI(eUIType::ExpBar);
		mUIs.insert(std::make_pair(eUIType::ExpBar, expBar));
		expBar->ImageLoad(L"ExpBar", L"..\\Resources\\Image\\UI\\InGame\\ExpBar.bmp");
		expBar->SetPos(Vector2(10.0f, 100.0f));
		
		Icon* Z = new Icon(eUIType::Z);
		mUIs.insert(std::make_pair(eUIType::Z, Z));
		Z->ImageLoad(L"Z", L"..\\Resources\\Image\\UI\\InGame\\Z.bmp");
		Z->SetPos(Vector2(78.0f, 16.0f));

		Icon* X = new Icon(eUIType::X);
		mUIs.insert(std::make_pair(eUIType::X, X));
		X->ImageLoad(L"X", L"..\\Resources\\Image\\UI\\InGame\\X.bmp");
		X->SetPos(Vector2(124.0f, 16.0f));

		Icon* C = new Icon(eUIType::C);
		mUIs.insert(std::make_pair(eUIType::C, C));
		C->ImageLoad(L"C", L"..\\Resources\\Image\\UI\\InGame\\C.bmp");
		C->SetPos(Vector2(170.0f, 16.0f));

		Icon* V = new Icon(eUIType::V);
		mUIs.insert(std::make_pair(eUIType::V, V));
		V->ImageLoad(L"V", L"..\\Resources\\Image\\UI\\InGame\\V.bmp");
		V->SetPos(Vector2(216.0f, 16.0f));

		playerInfoPanel->AddChild(hpBar);
		playerInfoPanel->AddChild(expBar);
		playerInfoPanel->AddChild(Z);
		playerInfoPanel->AddChild(X);
		playerInfoPanel->AddChild(C);
		playerInfoPanel->AddChild(V);

		Panel* difficultyPanel = new Panel(eUIType::Difficulty);
		mUIs.insert(std::make_pair(eUIType::Difficulty, difficultyPanel));
		difficultyPanel->ImageLoad(L"Difficulty", L"..\\Resources\\Image\\UI\\InGame\\Difficulty.bmp");
		difficultyPanel->SetPos(Vector2(Window_Width - 140, 30));

		DifficultyHUD* difficultyBar = new DifficultyHUD(eUIType::DifficultyBar);
		mUIs.insert(std::make_pair(eUIType::DifficultyBar, difficultyBar));
		difficultyBar->ImageLoad(L"DifficultyBar", L"..\\Resources\\Image\\UI\\InGame\\DifficultyBar.bmp");
		difficultyBar->SetPos(Vector2::Zero);

		difficultyPanel->AddChild(difficultyBar);

		Panel* bossHp = new Panel(eUIType::BossHp);
		mUIs.insert(std::make_pair(eUIType::BossHp, bossHp));
		bossHp->ImageLoad(L"BossHp", L"..\\Resources\\Image\\UI\\InGame\\BossHpBarE.bmp");
		bossHp->SetPos(Vector2(141, 30));

		BossHpBar* bossHpBarF = new BossHpBar(eUIType::BossHpBar);
		mUIs.insert(std::make_pair(eUIType::BossHpBar, bossHpBarF));
		bossHpBarF->ImageLoad(L"BossHpBar", L"..\\Resources\\Image\\UI\\InGame\\BossHpBarF.bmp");
		bossHpBarF->SetPos(Vector2::Zero);

		bossHp->AddChild(bossHpBarF);*/
	}
}