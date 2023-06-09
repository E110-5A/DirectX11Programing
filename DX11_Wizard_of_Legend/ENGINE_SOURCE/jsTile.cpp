#include "jsTile.h"
#include "jsConstantBuffer.h"
#include "jsRenderer.h"
#include "jsResources.h"
#include "jsTileRenderer.h"

#include "jsSpriteRenderer.h"

namespace js
{
	Tile::Tile()
		: GameObject()
		, mCollider(nullptr)
		, mAnimator(nullptr)
		, mTileType(eTileCollider::Platform)
		, mLocation(Vector2::Zero)
		, mTileSize(Vector2::Zero)
		, mTileSetIndex(Vector2::Zero)
	{
	}
	Tile::~Tile()
	{
	}
	void Tile::Initialize()
	{
		GameObject::Initialize();
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		sr->SetMaterial(Resources::Find<Material>(L"ObjectMaterial"));

		mCollider = AddComponent<Collider2D>();
		mAnimator = AddComponent<Animator>();

		mTileType = eTileCollider::Platform;
		mLocation = Vector2::Zero;

		mTileSize = Vector2(64.0f, 64.0f);

		mHomeAtlas = Resources::Find<Texture>(L"HomeTile64");
		mAirAtlas = Resources::Find<Texture>(L"AirTile");
		mFireAtlas = Resources::Find<Texture>(L"FireTile");
		mIceAtlas = Resources::Find<Texture>(L"IceTile");
		InitTileAnimator();

		//mTransform->SetScale(Vector3(1.5f, 1.5f, 1.0f));
		mCollider->SetSize(Vector2(1.0f, 1.0f));
		mAnimator->Play(L"Home00", false);
	}
	void Tile::Update()
	{
		GameObject::Update();
	}
	void Tile::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Tile::Render()
	{
		GameObject::Render();
	}
	void Tile::EditTile(eTileSet tileSet, eTileCollider tileCollider, Vector2 tileIndex)
	{
		SetColliderType(tileCollider);

		std::wstring animatoinName;

		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			animatoinName += L"Home";
		}
			break;
		case js::eTileSet::Air:
		{
			animatoinName += L"Air";
		}
			break;
		case js::eTileSet::Fire:
		{
			animatoinName += L"Fire";
		}
			break;
		case js::eTileSet::Ice:
		{
			animatoinName += L"Ice";
		}
			break;
		default:
			break;
		}

		animatoinName += std::to_wstring((int)tileIndex.x);
		animatoinName += std::to_wstring((int)tileIndex.y);

		mAnimator->Play(animatoinName, false);
	}

	void Tile::EditRoomTileLB(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home04", false);
		}
			break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
			break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
			break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
			break;
		}
	}

	void Tile::EditRoomTileRB(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home14", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditRoomTileLT(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home05", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditRoomTileRT(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home15", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditTrackTileLB(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home12", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditTrackTileRB(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home02", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditTrackTileLT(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home30", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditTrackTileRT(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home20", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditTileB(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home03", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditTileT(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home13", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditTileL(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home01", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditTileR(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home11", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}	

	void Tile::EditWallUpTile(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Wall);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home21", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditWallDownTile(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Platform);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home22", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::EditCenterTile(eTileSet tileSet)
	{
		SetColliderType(eTileCollider::Platform);
		switch (tileSet)
		{
		case js::eTileSet::Home:
		{
			mAnimator->Play(L"Home10", false);
		}
		break;
		case js::eTileSet::Air:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Fire:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		case js::eTileSet::Ice:
		{
			mAnimator->Play(L"Home04", false);
		}
		break;
		}
	}

	void Tile::SetLocation(Vector2 location)
	{
		mLocation = location;
		Vector2 scale = mCollider->GetSize();
		mTransform->SetPosition( Vector3( mLocation.x* scale.x, mLocation.y * scale.y, 1.0f ) );
	}

	void Tile::InitTileAnimator()
	{		
		{
			mAnimator->Create(L"Home00", mHomeAtlas, Vector2(0.0f, 0.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home10", mHomeAtlas, Vector2(64.0f, 0.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home20", mHomeAtlas, Vector2(128.0f, 0.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home30", mHomeAtlas, Vector2(192.0f, 0.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home01", mHomeAtlas, Vector2(0.0f, 64.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home11", mHomeAtlas, Vector2(64.0f, 64.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home21", mHomeAtlas, Vector2(128.0f, 64.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home31", mHomeAtlas, Vector2(192.0f, 64.0f), mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home02", mHomeAtlas, Vector2(0.0f, 128.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home12", mHomeAtlas, Vector2(64.0f, 128.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home22", mHomeAtlas, Vector2(128.0f, 128.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home32", mHomeAtlas, Vector2(192.0f, 128.0f), mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home03", mHomeAtlas, Vector2(0.0f, 192.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home13", mHomeAtlas, Vector2(64.0f, 192.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home23", mHomeAtlas, Vector2(128.0f, 192.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home33", mHomeAtlas, Vector2(192.0f, 192.0f), mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home04", mHomeAtlas, Vector2(0.0f, 256.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home14", mHomeAtlas, Vector2(64.0f, 256.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home24", mHomeAtlas, Vector2(128.0f, 256.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home34", mHomeAtlas, Vector2(192.0f, 256.0f), mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home05", mHomeAtlas, Vector2(0.0f, 320.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home15", mHomeAtlas, Vector2(64.0f, 320.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home25", mHomeAtlas, Vector2(128.0f, 320.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home35", mHomeAtlas, Vector2(192.0f, 320.0f), mTileSize, Vector2::Zero, 1, 0.1f);
		}
	}
}
