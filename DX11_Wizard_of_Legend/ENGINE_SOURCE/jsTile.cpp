#include "jsTile.h"
#include "jsConstantBuffer.h"
#include "jsRenderer.h"
#include "jsResources.h"
#include "jsTileRenderer.h"











namespace js
{
	Tile::Tile()
		: GameObject()
		, mAtlas(nullptr)
		, mCollider(nullptr)
		, mTileRenderer(nullptr)
		, mColliderType(eTileCollider::Platform)
		, mLocation(Vector2::Zero)
		, mTileSetIndex(Vector2::Zero)
	{
	}
	Tile::~Tile()
	{
		int a = 0;
	}
	void Tile::Initialize()
	{
		mTransform = AddComponent<Transform>();
		mCollider = AddComponent<Collider2D>();
		mTileRenderer = AddComponent<TileRenderer>();

		mTileRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mTileRenderer->SetMaterial(Resources::Find<Material>(L"TileMaterial"));

		// �ʱⰪ
		mAtlas = Resources::Find<Texture>(L"HomeTile");
		mColliderType = eTileCollider::Platform;
		mLocation = Vector2::Zero;

		mTileSetIndex = Vector2::Zero;
		mTileSize = Vector2(32.0f, 32.0f);
		mTilesetSize = Vector2(192.0f, 320.0f);

		TileSet tile;
		float width = (float)mAtlas->GetWidth();
		float height = (float)mAtlas->GetHeight();
		Vector2 lt = Vector2(mTileSetIndex * mTileSize);
		lt = Vector2(lt.x / width, lt.y / height);

		tile.leftTop = lt;
		tile.tileSize = mTileSize;
		tile.tilesetSize = mTilesetSize;
		mTileInfo = tile;		
	}
	void Tile::Update()
	{
	}
	void Tile::FixedUpdate()
	{
	}
	void Tile::Render()
	{
	}
	void Tile::EditTile(std::shared_ptr<Texture> atlas, eTileCollider tileCollider, Vector2 tileIndex, Vector2 tileSize, Vector2 tilesetSize)
	{
		mAtlas = atlas;
		mColliderType = tileCollider;
		mTileSetIndex = tileIndex;

		TileSet tile;
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();
		Vector2 lt = Vector2(mTileSetIndex * tileSize);
		lt = Vector2(lt.x / width, lt.y / height);

		tile.leftTop = lt;
		tile.tileSize = tileSize;
		tile.tilesetSize = tilesetSize;
		mTileInfo = tile;

		mTileRenderer->SetTileInfo(tile);
	}
}
