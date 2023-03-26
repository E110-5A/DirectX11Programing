#include "jsSceneManager.h"

#include "jsLogoScene.h"
#include "jsTitleScene.h"
#include "jsPlayScene.h"



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
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Play]->SetName(L"PlayScene");

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

		// �ٲ� dontDestory ������Ʈ�� ���������� ���� �Ѱ�����Ѵ�.
		MoveDontDestoryObjects(type);

		mActiveScene->OnEnter();
	}

	void SceneManager::MoveDontDestoryObjects(eSceneType type)
	{
		// Dont Destroy Object ��������
		std::vector<GameObject*> gameObjs = mActiveScene->GetDontDestroyGameObjects();

		// �� ����
		mActiveScene = mScenes[(UINT)type];

		// ������Ʈ �ű��
		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}
	}
}