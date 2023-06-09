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

	void TileMap::EditTileToRoom(Vector2 lbLocation, Vector2 size, eTileSet tileSet)
	{
		for (int y = (int)lbLocation.y; y <= (int)lbLocation.y + size.y; ++y)
		{
			for (int x = (int)lbLocation.x; x <= (int)lbLocation.x + size.x; ++x)
			{
				// b, t 찾기 y 축
				if (y == lbLocation.y)
				{
					if (x == lbLocation.x) // LB
					{
						tiles[y][x]->EditRoomTileLB(tileSet);
					}
					else if (x == lbLocation.x + size.x) // RB
					{
						tiles[y][x]->EditRoomTileRB(tileSet);
					}
					else // B
					{
						tiles[y][x]->EditTileB(tileSet);
					}
				}
				else if (y == lbLocation.y + size.y)
				{
					if (x == lbLocation.x) // LT
					{
						tiles[y][x]->EditRoomTileLT(tileSet);
					}
					else if (x == lbLocation.x + size.x) // RT
					{
						tiles[y][x]->EditRoomTileRT(tileSet);
					}
					else // T Top은 조금 특수함
					{
						tiles[y][x]->EditTileT(tileSet);
					}
				}
				else
				{
					if (x == lbLocation.x) // L
					{
						tiles[y][x]->EditTileL(tileSet);
					}
					else if (x == lbLocation.x + size.x) // R
					{
						tiles[y][x]->EditTileR(tileSet);
					}
					else // Center
					{
						// 위에서 3칸 예외처리
						if (y == lbLocation.y + size.y - 1)
							tiles[y][x]->EditWallUpTile(tileSet);
						else if (y == lbLocation.y + size.y - 2)
							tiles[y][x]->EditWallDownTile(tileSet);
						else
							tiles[y][x]->EditCenterTile(tileSet);
					}
				}
			}
		}
	}

	void TileMap::EditTileToHorizonTrack(Vector2 lbLocation, Vector2 size, eTileSet tileSet)
	{
		for (int y = (int)lbLocation.y; y <= (int)lbLocation.y + size.y; ++y)
		{
			for (int x = (int)lbLocation.x; x <= (int)lbLocation.x + size.x; ++x)
			{
				// b, t 찾기 y 축
				if (y == lbLocation.y)
				{
					if (x == lbLocation.x) // LB
					{
						tiles[y][x]->EditTrackTileLB(tileSet);
					}
					else if (x == lbLocation.x + size.x) // RB
					{
						tiles[y][x]->EditTrackTileRB(tileSet);
					}
					else // B
					{
						tiles[y][x]->EditTileB(tileSet);
					}
				}
				else if (y == lbLocation.y + size.y)
				{
					if (x == lbLocation.x) // LT
					{
						tiles[y][x]->EditTrackTileLT(tileSet);
					}
					else if (x == lbLocation.x + size.x) // RT
					{
						tiles[y][x]->EditTrackTileRT(tileSet);
					}
					else // T
					{
						tiles[y][x]->EditTileT(tileSet);
					}
				}
				else
				{
					if (x == lbLocation.x) // L
					{
						tiles[y][x]->EditCenterTile(tileSet);
					}
					else if (x == lbLocation.x + size.x) // R
					{
						tiles[y][x]->EditCenterTile(tileSet);
					}
					else // Center
					{
						// 위에서 3칸 예외처리
						if (y == lbLocation.y + size.y - 1)
							tiles[y][x]->EditWallUpTile(tileSet);
						else if (y == lbLocation.y + size.y - 2)
							tiles[y][x]->EditWallDownTile(tileSet);
						else
							tiles[y][x]->EditCenterTile(tileSet);
					}
				}
			}
		}
	}

	void TileMap::EditTileToVerticalTrack(Vector2 lbLocation, Vector2 size, eTileSet tileSet)
	{
		for (int y = (int)lbLocation.y; y <= (int)lbLocation.y + size.y; ++y)
		{
			for (int x = (int)lbLocation.x; x <= (int)lbLocation.x + size.x; ++x)
			{
				// b, t 찾기 y 축
				if (y == lbLocation.y)
				{
					if (x == lbLocation.x) // LB
					{
						tiles[y][x]->EditTrackTileLB(tileSet);
					}
					else if (x == lbLocation.x + size.x) // RB
					{
						tiles[y][x]->EditTrackTileRB(tileSet);
					}
					else // B
					{
						tiles[y][x]->EditCenterTile(tileSet);
					}
				}
				else if (y == lbLocation.y + size.y)
				{
					if (x == lbLocation.x) // LT
					{
						tiles[y][x]->EditTrackTileLT(tileSet);
					}
					else if (x == lbLocation.x + size.x) // RT
					{
						tiles[y][x]->EditTrackTileRT(tileSet);
					}
					else // T
					{
						tiles[y][x]->EditCenterTile(tileSet);
					}
				}
				else
				{
					if (x == lbLocation.x) // L
					{
						tiles[y][x]->EditTileL(tileSet);
					}
					else if (x == lbLocation.x + size.x) // R
					{
						tiles[y][x]->EditTileR(tileSet);
					}
					else // Center
					{
						// 위에서 3칸 예외처리
						if (y == lbLocation.y + size.y - 1)
							tiles[y][x]->EditWallUpTile(tileSet);
						else if (y == lbLocation.y + size.y - 2)
							tiles[y][x]->EditWallDownTile(tileSet);
						else
							tiles[y][x]->EditCenterTile(tileSet);
					}
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
				delete tiles[y][x];
				tiles[y][x] = nullptr;
			}
		}
	}		
}