#pragma once
#include "jsEntity.h"
#include "jsTexture.h"
#include "jsTile.h"
#include "jsScene.h"
namespace js
{
	

	class Tile;
	class TileMap : public Entity
	{
	public:
		TileMap();
		virtual ~TileMap();

		void SetMapSize(Vector2 mapSize, Scene* scene);
		void EditTile(Vector2 v1, Vector2 v2, eTileSet tileSet, eTileCollider tileCollider, Vector2 tileSetIndex);
		void ClearTiles();
	private:
		Vector2							mMapSize;		// 타일 개수
		std::vector<std::vector<Tile*>>	tiles;
		
	};
}


