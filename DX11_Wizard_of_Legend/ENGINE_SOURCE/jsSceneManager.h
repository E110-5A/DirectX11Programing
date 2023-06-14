#pragma once
#include "jsScene.h"
#include "jsTileMap.h"
#include "jsPlayer.h"

namespace js
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetScene(eSceneType type) { return mScenes[(UINT)type]; };
		static void MoveDontDestoryObjects(eSceneType type);

#pragma region TileMap Func
		static void SetMapSize(eSceneType sceneType, Vector2 mapSize, Scene* scene);
		// 0,0 = Left_Bottom
		static void EditTile(eSceneType sceneType, Vector2 v1, Vector2 v2, eTileCollider tileCollider, Vector2 tileIndex);
		// 가로3칸 세로 4칸 이상부터 가능
		static void EditTileToRoom(eSceneType sceneType, Vector2 ltLocation, Vector2 size, eTileSet tileSet);
		static void EditTileToHorizonTrack(eSceneType sceneType, Vector2 ltLocation, Vector2 size, eTileSet tileSet);
		static void EditTileToVerticalTrack(eSceneType sceneType, Vector2 ltLocation, Vector2 size, eTileSet tileSet);
		static void EditTileToSpawnPoint(eSceneType sceneType, Vector2 ltLocation);
#pragma endregion

#pragma region GameObject
		static void SetPlayer(Player* player) { mPlayer = player; }
		static Player* GetPlayer() { return mPlayer; }
#pragma endregion

	private:
		static std::vector<Scene*>		mScenes;
		static std::vector<TileMap*>	mTileMaps;
		static Scene*					mActiveScene;
		static Player*					mPlayer;
	};
}
