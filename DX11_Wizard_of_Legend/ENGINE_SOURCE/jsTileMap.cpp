#include "jsTileMap.h"
#include "jsResources.h"
namespace js
{
	TileMap::TileMap()
	{
		// 여기서 리소스 가져옵니다
		mHomeAtlas = Resources::Find<Texture>(L"HomeTile");
		mAirAtlas  = Resources::Find<Texture>(L"AirTile");
		mFireAtlas = Resources::Find<Texture>(L"FireTile");
		mIceAtlas  = Resources::Find<Texture>(L"IceTile");
		mTileSize = Vector2(32.0f, 32.0f);
	}
	TileMap::~TileMap()
	{
		tiles.clear();
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
				switch (tileSet)
				{
				case js::eTileSet::Home:
					tiles[y][x]->EditTile(mHomeAtlas, tileCollider, tileIndex, mTileSize, Vector2(192.0f, 320.0f));
					break;
				case js::eTileSet::Air:
					tiles[y][x]->EditTile(mHomeAtlas, tileCollider, tileIndex, mTileSize, Vector2(192.0f, 320.0f));
					break;
				case js::eTileSet::Fire:
					tiles[y][x]->EditTile(mHomeAtlas, tileCollider, tileIndex, mTileSize, Vector2(192.0f, 320.0f));
					break;
				case js::eTileSet::Ice:
					tiles[y][x]->EditTile(mHomeAtlas, tileCollider, tileIndex, mTileSize, Vector2(192.0f, 320.0f));
					break;
				}
			}
		}
	}

	void TileMap::ClearTiles()
	{
		for (int y = 0; y < mMapSize.y; ++y)
		{
			for (int x = 0; x < mMapSize.x; x++)
			{
				//tiles[y].erase(tiles[y].begin(), tiles[y].end());
				delete tiles[y][x];
				tiles[y][x] = nullptr;
			}
		}
	}		
}