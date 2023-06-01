#pragma once
#include "jsGameObject.h"
#include "jsTexture.h"
#include "GameObjectComponents.h"
#include "jsScene.h"

namespace js
{
	struct TileSet
	{
		Vector2 leftTop;		// �̹��� ��������							index�� ���� �ٸ�
		Vector2 spriteSize;		// ������������ �߶� ���� ���� �ȼ� ����		32 x 32
		Vector2 offset;			// ������ ���� ��ǥ							0 x 0
		Vector2 atlasSize;		// �ؽ��� �̹��� ũ��							? x ?
		float duration;			// ������ �ð� ����							0.1

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
		Transform*	mTransform;			// ���Ŀ� loaction�� ���� pos���� �ٲ�
		Animator*	mAnimator;			// Ÿ�� �̹��� ������ (TileRenderer�� ���� ����� �ʿ������
		Collider2D* mCollider;			// �浹 ����

	private:
		std::shared_ptr<Texture>	mAtlas;
		eTileCollider				mColliderType;
		Vector2						mLocation;		// (1,1)  (2,3) �̷������� �򸮰� ��

	private:
		Vector2						mTileSetIndex;
		Vector2						mTileSize;
		Vector2						mAtlasSize;
	};
}