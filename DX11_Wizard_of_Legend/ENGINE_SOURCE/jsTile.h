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

		void SetColliderType(eTileCollider type) { mColliderType = type; }
		void SetTileIndex(Vector2 index) { mTileSetIndex = index; }
		void SetLocation(Vector2 location) { mLocation = location; }

		eTileCollider GetTileColliderType() { return mColliderType; }
				

	public:
		void InitTileAnimator();

	public:
		void SelfDelete() { delete this; }

	private:
		Collider2D*		mCollider;			// 충돌 영역
		Animator*		mAnimator;

	private:
		eTileCollider				mColliderType;
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