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
		void SetTileSize(Vector2 tileSize) { mTileSize = tileSize; }
		void EditTile(Vector2 v1, Vector2 v2, eTileSet tileSet, eTileCollider tileCollider, Vector2 tileSetIndex);
		void ClearTiles();
	private:
		Vector2							mMapSize;
		Vector2							mTileSize;
		std::vector<std::vector<Tile*>>	tiles;
		
		// 하드코딩
		std::shared_ptr<Texture>		mHomeAtlas;
		std::shared_ptr<Texture>		mAirAtlas;
		std::shared_ptr<Texture>		mFireAtlas;
		std::shared_ptr<Texture>		mIceAtlas;
	};
}


