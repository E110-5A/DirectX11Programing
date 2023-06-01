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
	}
	TileMap::~TileMap()
	{
	}
	void TileMap::SetMapSize(Vector2 mapSize, Scene* scene)
	{
		// 타일 개수를 정합니다
		mMapSize = mapSize;
		tiles = std::vector<std::vector<Tile>>(mapSize.y, std::vector<Tile>(mapSize.x));
		for (int y = 0; y < mMapSize.y; ++y)
		{
			for (int x = 0; x < mMapSize.x; ++x)
			{
				tiles[y][x].Clear();
				tiles[y][x].SetLocation(Vector2(x, y));
				tiles[y][x].PutInScene(scene);
			}
		}
	}
	void TileMap::SetTileSize(Vector2 tileSize)
	{
		for (int y = 0; y < mMapSize.y; ++y)
		{
			for (int x = 0; x < mMapSize.x; ++x)
			{
				tiles[y][x].SetTileSize(tileSize);
			}
		}
	}
	void TileMap::EditTile(Vector2 v1, Vector2 v2, eTileSet tileSet, eTileCollider tileCollider, Vector2 tileSetIndex)
	{
		// v1 벡터와 v2 벡터 사이에 포함되는 벡터들을 다음과 같이 편집합니다
		for (int y = v1.y; y < v2.y; ++y)
		{
			for (int x = v1.x; x < v2.x; ++x)
			{
				switch (tileSet)
				{
				case js::eTileSet::Home:
					tiles[y][x].SetAtlas(mHomeAtlas);
					tiles[y][x].SetAtlasSize(Vector2(192.0f, 320.0f));
					break;
				case js::eTileSet::Air:
					tiles[y][x].SetAtlas(mAirAtlas);
					break;
				case js::eTileSet::Fire:
					tiles[y][x].SetAtlas(mFireAtlas);
					break;
				case js::eTileSet::Ice:
					tiles[y][x].SetAtlas(mIceAtlas);
					break;
				}
				tiles[y][x].SetColliderType(tileCollider);
				tiles[y][x].SetTileSetIndex(tileSetIndex);
			}
		}
	}
		
}