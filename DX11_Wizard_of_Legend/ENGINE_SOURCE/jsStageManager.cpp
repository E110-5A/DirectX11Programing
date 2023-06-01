#include "jsStageManager.h"
#include "jsSceneManager.h"
namespace js
{
	void StageManager::Initialize()
	{
		Scene* homeScene = SceneManager::GetScene(eSceneType::Home);
		SetMapSize(Vector2(10.0f, 10.0f), homeScene);

		Scene* Stage01 = SceneManager::GetScene(eSceneType::Stage01);
		SetMapSize(Vector2(100.0f, 100.0f), Stage01);
	}
	void StageManager::Update()
	{
	}
	void StageManager::FixedUpdate()
	{
	}
	void StageManager::Render()
	{
	}
	void StageManager::Destroy()
	{
	}
	void StageManager::Release()
	{
	}
	void StageManager::SetMapSize(Vector2 mapSize, Scene* scene)
	{
		mTileMap.SetMapSize(mapSize, scene);
	}
	void StageManager::SetTileSize(Vector2 tileSize)
	{
		mTileMap.SetTileSize(tileSize);
	}
	void StageManager::EditTile(Vector2 v1, Vector2 v2, eTileSet tileSet, eTileCollider tileCollider, Vector2 tileSetIndex)
	{
		mTileMap.EditTile(v1, v2, tileSet, tileCollider, tileSetIndex);
	}
}