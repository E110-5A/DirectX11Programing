#include "jsSceneManager.h"
#include "jsTransform.h"
#include "jsMeshRenderer.h"
#include "jsRenderer.h"
#include "jsResources.h"
#include "jsTexture.h"
#include "jsPlayerScript.h"
#include "jsCamera.h"
#include "jsCameraScript.h"
#include "jsSpriteRenderer.h"
#include "jsGridScript.h"
#include "jsTitleScene.h"
#include "jsPlayScene.h"

namespace js
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Tilte] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();

		mActiveScene = mScenes[(UINT)eSceneType::Tilte];

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
		std::vector<GameObject*> gameObjs 
			= mActiveScene->GetDontDestroyGameObjects();
		mActiveScene = mScenes[(UINT)type];
		
		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}

		mActiveScene->OnEnter();
	}
}