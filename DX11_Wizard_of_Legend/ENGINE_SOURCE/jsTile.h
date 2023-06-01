#pragma once
#include "jsGameObject.h"
#include "jsTexture.h"
#include "GameObjectComponents.h"
#include "jsScene.h"

namespace js
{
	struct TileSet
	{
		Vector2 leftTop;		// 이미지 시작지점							index에 따라 다름
		Vector2 spriteSize;		// 시작지점부터 잘라낼 가로 세로 픽셀 길이		32 x 32
		Vector2 offset;			// 렌더링 조정 좌표							0 x 0
		Vector2 atlasSize;		// 텍스쳐 이미지 크기							? x ?
		float duration;			// 프레임 시간 간격							0.1

		TileSet()
			: leftTop(Vector2::Zero)
			, spriteSize(Vector2::Zero)
			, offset(Vector2::Zero)
			, atlasSize(Vector2::Zero)
			, duration(0.1f)
		{}
	};

	enum class eTileSet
	{
		Home,
		Air,
		Fire,
		Ice,
	};
	enum class eTileCollider
	{
		Wall,
		Platform,
		FallArea,
	};

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
		void Clear();

	public:
		void PutInScene(Scene* scene) { scene->AddGameObject(this, eLayerType::Tile); }

		void SetAtlas(std::shared_ptr<Texture> atlas) { mAtlas = atlas; }
		void SetColliderType(eTileCollider type) { mColliderType = type; }
		void SetTileSetIndex(Vector2 index) { mTileSetIndex = index; }

		void SetTileSize(Vector2 size) { mTileSize = size; }
		void SetAtlasSize(Vector2 size) { mAtlasSize = size; }
		void SetLocation(Vector2 location) { mLocation = location; }
	public:
		void BindShader();
		
	private:
		Transform*	mTransform;			// 추후에 loaction에 따라 pos값이 바뀜
		Animator*	mAnimator;			// 타일 이미지 렌더용 (TileRenderer를 따로 만들면 필요없긴함
		Collider2D* mCollider;			// 충돌 영역

	private:
		std::shared_ptr<Texture>	mAtlas;
		eTileCollider				mColliderType;
		Vector2						mLocation;		// (1,1)  (2,3) 이런식으로 깔리게 됨

	private:
		Vector2						mTileSetIndex;
		Vector2						mTileSize;
		Vector2						mAtlasSize;
	};
}