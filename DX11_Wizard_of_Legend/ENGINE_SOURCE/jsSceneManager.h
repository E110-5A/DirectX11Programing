#pragma once
#include "jsScene.h"
#include "jsTileMap.h"

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
		static void SetTileSize(eSceneType sceneType, Vector2 tileSize);
		static void EditTile(eSceneType sceneType, Vector2 v1, Vector2 v2, eTileSet tileSet, eTileCollider tileCollider, Vector2 tileIndex);
#pragma endregion

	private:
		static std::vector<Scene*>		mScenes;
		static std::vector<TileMap*>	mTileMaps;
		static Scene*					mActiveScene;

	};
}
