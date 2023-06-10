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
	std::vector<TileMap*> SceneManager::mTileMaps = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = nullptr;
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

		mTileMaps.resize((UINT)eSceneType::End);

		mTileMaps[(UINT)eSceneType::Logo]			= new TileMap();
		mTileMaps[(UINT)eSceneType::Title]			= new TileMap();
		mTileMaps[(UINT)eSceneType::Home]			= new TileMap();
		mTileMaps[(UINT)eSceneType::Stage01]		= new TileMap();
		mTileMaps[(UINT)eSceneType::Stage01Boss]	= new TileMap();
		mTileMaps[(UINT)eSceneType::Stage02]		= new TileMap();
		mTileMaps[(UINT)eSceneType::Stage02Boss]	= new TileMap();

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
		for (TileMap* tileMap : mTileMaps)
		{
			delete tileMap;
			tileMap = nullptr;
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

	void SceneManager::SetMapSize(eSceneType sceneType, Vector2 mapSize, Scene* scene)
	{
		mTileMaps[(UINT)sceneType]->SetMapSize(mapSize, scene);
	}
	void SceneManager::EditTile(eSceneType sceneType, Vector2 v1, Vector2 v2, eTileCollider tileCollider, Vector2 tileIndex)
	{
		switch (sceneType)
		{
		case js::enums::eSceneType::Home:
		{
			mTileMaps[(UINT)sceneType]->EditTile(v1, v2, eTileSet::Home, tileCollider, tileIndex);
		}
			break;
		case js::enums::eSceneType::Stage01:
		{
			mTileMaps[(UINT)sceneType]->EditTile(v1, v2, eTileSet::Home, tileCollider, tileIndex);
		}
			break;
		case js::enums::eSceneType::Stage01Boss:
		{
			mTileMaps[(UINT)sceneType]->EditTile(v1, v2, eTileSet::Home, tileCollider, tileIndex);
		}
			break;
		case js::enums::eSceneType::Stage02:
		{
			mTileMaps[(UINT)sceneType]->EditTile(v1, v2, eTileSet::Home, tileCollider, tileIndex);
		}
			break;
		case js::enums::eSceneType::Stage02Boss:
		{
			mTileMaps[(UINT)sceneType]->EditTile(v1, v2, eTileSet::Home, tileCollider, tileIndex);
		}
			break;
		}
	}
	
	void SceneManager::EditTileToRoom(eSceneType sceneType, Vector2 ltLocation, Vector2 size, eTileSet tileSet)
	{
		mTileMaps[(UINT)sceneType]->EditTileToRoom(ltLocation, size, tileSet);
	}

	void SceneManager::EditTileToHorizonTrack(eSceneType sceneType, Vector2 ltLocation, Vector2 size, eTileSet tileSet)
	{
		mTileMaps[(UINT)sceneType]->EditTileToHorizonTrack(ltLocation, size, tileSet);
	}

	void SceneManager::EditTileToVerticalTrack(eSceneType sceneType, Vector2 ltLocation, Vector2 size, eTileSet tileSet)
	{
		mTileMaps[(UINT)sceneType]->EditTileToVerticalTrack(ltLocation, size, tileSet);
	}

	void SceneManager::EditTileToSpawnPoint(eSceneType sceneType, Vector2 ltLocation)
	{
		Transform* playerTransform = mPlayer->GetComponent<Transform>();
		Transform* targetTransfrom = mTileMaps[(UINT)sceneType]->GetTile(ltLocation)->GetComponent<Transform>();
		playerTransform->SetPosition( targetTransfrom->GetPosition() );
	}
	
}