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


		// ����3ĭ ���� 4ĭ �̻���� ����
		void EditTileToRoom(Vector2 ltLocation, Vector2 size, eTileSet tileSet);
		void EditTileToHorizonTrack(Vector2 ltLocation, Vector2 size, eTileSet tileSet);
		void EditTileToVerticalTrack(Vector2 ltLocation, Vector2 size, eTileSet tileSet);

		void ClearTiles();
	private:
		Vector2							mMapSize;		// Ÿ�� ����
		std::vector<std::vector<Tile*>>	tiles;
		
	};
}


