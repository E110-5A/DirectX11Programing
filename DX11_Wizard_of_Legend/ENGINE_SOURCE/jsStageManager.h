#pragma once
#include "jsTileMap.h"
#include "jsScene.h"

namespace js
{
	class StageManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();


#pragma region TileMap Func
		static void SetMapSize(Vector2 mapSize, Scene* scene);
		static void SetTileSize(Vector2 tileSize);
		static void EditTile(Vector2 v1, Vector2 v2, eTileSet tileSet, eTileCollider tileCollider, Vector2 tileSetIndex);
#pragma endregion

	private:
		// Ÿ�� �׷��� �ʿ��ҵ�
		static TileMap mTileMap;
		
		// �Ϻ� ��Ȱ�� ������Ʈ�� ���⿡ ����

	};
}