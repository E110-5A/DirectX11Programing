#include "jsSceneManager.h"

#include "jsLogoScene.h"
#include "jsTitleScene.h"
#include "jsHomeScene.h"
#include "jsStage01.h"
#include "jsStage01Boss.h"
#include "jsStage02.h"
#include "jsStage02Boss.h"


namespace js
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Logo]->SetName(L"LogoScene");
		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Title]->SetName(L"TitleScene");
		mScenes[(UINT)eSceneType::Home] = new HomeScene();
		mScenes[(UINT)eSceneType::Home]->SetName(L"HomeScene");
		mScenes[(UINT)eSceneType::Stage01] = new Stage01Scene();
		mScenes[(UINT)eSceneType::Stage01]->SetName(L"Stage01Scene");
		mScenes[(UINT)eSceneType::Stage01Boss] = new Stage01BossScene();
		mScenes[(UINT)eSceneType::Stage01Boss]->SetName(L"Stage01BossScene");
		mScenes[(UINT)eSceneType::Stage02] = new Stage02BossScene();
		mScenes[(UINT)eSceneType::Stage02]->SetName(L"Stage02Scene");
		mScenes[(UINT)eSceneType::Stage02Boss] = new Stage02Scene();
		mScenes[(UINT)eSceneType::Stage02Boss]->SetName(L"Stage02BossScene");

		mActiveScene = mScenes[(UINT)eSceneType::Logo];

		for (Scene* scene : mScenes)
		{
			scene->Initialize();
		}
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		if (mActiveScene)
			mActiveScene->OnExit();

		// 바뀔때 dontDestory 오브젝트는 다음씬으로 같이 넘겨줘야한다.
		MoveDontDestoryObjects(type);

		mActiveScene->OnEnter();
	}

	void SceneManager::MoveDontDestoryObjects(eSceneType type)
	{
		// Dont Destroy Object 가져오기
		std::vector<GameObject*> gameObjs = mActiveScene->GetDontDestroyGameObjects();

		// 씬 변경
		mActiveScene = mScenes[(UINT)type];

		// 오브젝트 옮기기
		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}
	}
}