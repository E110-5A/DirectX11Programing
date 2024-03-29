#pragma once
#include "jsGameObject.h"
#include "GameObjectComponents.h"
#include "jsTileRenderer.h"
#include "jsScene.h"
#include "TileStruct.h"
namespace js
{
	class Tile : public GameObject
	{
	public:
		Tile();
		virtual ~Tile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		void PutInScene(Scene* scene) { scene->AddGameObject(this, eLayerType::Tile); }

		void EditTile(eTileSet tileSet, eTileCollider tileCollider, Vector2 tileIndex);

	public:
		void EditRoomTileLB(eTileSet tileSet);
		void EditRoomTileRB(eTileSet tileSet);
		void EditRoomTileLT(eTileSet tileSet);
		void EditRoomTileRT(eTileSet tileSet);

		void EditTrackTileLB(eTileSet tileSet);
		void EditTrackTileRB(eTileSet tileSet);
		void EditTrackTileLT(eTileSet tileSet);
		void EditTrackTileRT(eTileSet tileSet);

		void EditTileB(eTileSet tileSet);
		void EditTileT(eTileSet tileSet);
		void EditTileL(eTileSet tileSet);
		void EditTileR(eTileSet tileSet);

		void EditWallUpTile(eTileSet tileSet);
		void EditWallDownTile(eTileSet tileSet);
		void EditCenterTile(eTileSet tileSet);

	public:
		void SetColliderType(eTileCollider type) { mTileType = type; }
		void SetTileIndex(Vector2 index) { mTileSetIndex = index; }
		void SetLocation(Vector2 location);

		eTileCollider GetTileCollisionType() { return mTileType; }
		
	public:
		void InitTileAnimator();

	public:
		void SelfDelete() { delete this; }

	private:
		Collider2D*		mCollider;			// 충돌 영역
		Animator*		mAnimator;

	private:
		eTileCollider				mTileType;
		Vector2						mLocation;		// (1,1)  (2,3) 이런식으로 깔리게 됨

	private:
		Vector2						mTileSetIndex;
		Vector2						mTileSize;

	private:
		std::shared_ptr<Texture>		mHomeAtlas;
		std::shared_ptr<Texture>		mAirAtlas;
		std::shared_ptr<Texture>		mFireAtlas;
		std::shared_ptr<Texture>		mIceAtlas;
	};
}