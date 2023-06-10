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

		Tile* GetTile(Vector2 location);

		void SetMapSize(Vector2 mapSize, Scene* scene);
		void EditTile(Vector2 v1, Vector2 v2, eTileSet tileSet, eTileCollider tileCollider, Vector2 tileSetIndex);


		// 가로3칸 세로 4칸 이상부터 가능
		void EditTileToRoom(Vector2 ltLocation, Vector2 size, eTileSet tileSet);
		void EditTileToHorizonTrack(Vector2 ltLocation, Vector2 size, eTileSet tileSet);
		void EditTileToVerticalTrack(Vector2 ltLocation, Vector2 size, eTileSet tileSet);

		void ClearTiles();
	private:
		Vector2							mMapSize;		// 타일 개수
		std::vector<std::vector<Tile*>>	tiles;
		
	};
}


