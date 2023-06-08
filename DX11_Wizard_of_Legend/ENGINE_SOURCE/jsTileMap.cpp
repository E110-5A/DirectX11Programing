#include "jsTileMap.h"
#include "jsResources.h"
namespace js
{
	TileMap::TileMap()
		: mMapSize(Vector2::Zero)
	{
	}
	TileMap::~TileMap()
	{
	}
	void TileMap::SetMapSize(Vector2 mapSize, Scene* scene)
	{
		tiles.clear();
		mMapSize = mapSize;
		tiles.resize(mapSize.y);
		for (size_t idx = 0; idx < mapSize.y; idx++)
		{
			tiles[idx].resize(mapSize.x);
		}

		// tiles = std::vector<std::vector<Tile*>>( mapSize.y, std::vector<Tile*>( mapSize.x, new Tile() ) );
		for (int y = 0; y < mMapSize.y; ++y)
		{
			for (int x = 0; x < mMapSize.x; ++x)
			{
				tiles[y][x] = new Tile();
				tiles[y][x]->Initialize();
				tiles[y][x]->SetLocation(Vector2((float)x, (float)y));
				tiles[y][x]->PutInScene(scene);
			}
		}
	}
	void TileMap::EditTile(Vector2 v1, Vector2 v2, eTileSet tileSet, eTileCollider tileCollider, Vector2 tileIndex)
	{
		// v1 벡터와 v2 벡터 사이에 포함되는 벡터들을 다음과 같이 편집합니다
		for (int y = (int)v1.y; y <= (int)v2.y; ++y)
		{
			for (int x = (int)v1.x; x <= (int)v2.x; ++x)
			{
				tiles[y][x]->EditTile(tileSet, tileCollider, tileIndex);
			}
		}
	}

	void TileMap::EditTileToRoom(Vector2 ltLocation, Vector2 size, eTileSet tileSet)
	{
		for (int y = (int)ltLocation.y; y <= (int)ltLocation.y + size.y; ++y)
		{
			for (int x = (int)ltLocation.x; x <= (int)ltLocation.x + size.x; ++x)
			{
				// lb,  rb 찾기
				// b, t 찾기
				// l, r 찾기
				// lt,  rt 찾기

				// center 찾기
			}
		}
	}

	void TileMap::EditTileToHorizonTrack(Vector2 ltLocation, Vector2 size, eTileSet tileSet)
	{
		for (int y = (int)ltLocation.y; y <= (int)ltLocation.y + size.y; ++y)
		{
			for (int x = (int)ltLocation.x; x <= (int)ltLocation.x + size.x; ++x)
			{
				// lb,  rb 찾기
				// b, t 찾기
				// lt, rt 찾기

				// center 찾기
			}
		}
	}

	void TileMap::EditTileToVerticalTrack(Vector2 ltLocation, Vector2 size, eTileSet tileSet)
	{
		for (int y = (int)ltLocation.y; y <= (int)ltLocation.y + size.y; ++y)
		{
			for (int x = (int)ltLocation.x; x <= (int)ltLocation.x + size.x; ++x)
			{
				// lb, rb 찾기
				// l, r 찾기
				// lt, rt 찾기

				// center 찾기
			}
		}
	}

	void TileMap::ClearTiles()
	{
		for (int y = 0; y < mMapSize.y; ++y)
		{
			for (int x = 0; x < mMapSize.x; x++)
			{				
				delete tiles[y][x];
				tiles[y][x] = nullptr;
			}
		}
	}		
}