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
		, mColliderType(eTileCollider::Platform)
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

		mColliderType = eTileCollider::Platform;
		mLocation = Vector2::Zero;

		mTileSize = Vector2(32.0f, 32.0f);

		mHomeAtlas = Resources::Find<Texture>(L"HomeTile");
		mAirAtlas = Resources::Find<Texture>(L"AirTile");
		mFireAtlas = Resources::Find<Texture>(L"FireTile");
		mIceAtlas = Resources::Find<Texture>(L"IceTile");
		InitTileAnimator();

		//mTransform->SetScale(Vector3(1.5f, 1.5f, 1.0f));
		mCollider->SetSize(Vector2(0.6f, 0.6f));
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

		SetColliderType(tileCollider);
		mAnimator->Play(animatoinName, false);
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
			mAnimator->Create(L"Home00", mHomeAtlas, Vector2(0.0f, 0.0f)		, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home10", mHomeAtlas, Vector2(32.0f, 0.0f)		, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home20", mHomeAtlas, Vector2(64.0f, 0.0f)		, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home30", mHomeAtlas, Vector2(96.0f, 0.0f)		, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home40", mHomeAtlas, Vector2(128.0f, 0.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home50", mHomeAtlas, Vector2(160.0f, 0.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home01", mHomeAtlas, Vector2(0.0f, 32.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home11", mHomeAtlas, Vector2(32.0f, 32.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home21", mHomeAtlas, Vector2(64.0f, 32.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home31", mHomeAtlas, Vector2(96.0f, 32.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home41", mHomeAtlas, Vector2(128.0f, 32.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home51", mHomeAtlas, Vector2(160.0f, 32.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home02", mHomeAtlas, Vector2(0.0f, 64.0f)		, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home12", mHomeAtlas, Vector2(32.0f, 64.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home22", mHomeAtlas, Vector2(64.0f, 64.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home32", mHomeAtlas, Vector2(96.0f, 64.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home42", mHomeAtlas, Vector2(128.0f, 64.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home52", mHomeAtlas, Vector2(160.0f, 64.0f)	, mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home03", mHomeAtlas, Vector2(0.0f, 96.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home13", mHomeAtlas, Vector2(32.0f, 96.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home23", mHomeAtlas, Vector2(64.0f, 96.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home33", mHomeAtlas, Vector2(96.0f, 96.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home43", mHomeAtlas, Vector2(128.0f, 96.0f), mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home53", mHomeAtlas, Vector2(160.0f, 96.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home04", mHomeAtlas, Vector2(0.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home14", mHomeAtlas, Vector2(32.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home24", mHomeAtlas, Vector2(64.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home34", mHomeAtlas, Vector2(96.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home44", mHomeAtlas, Vector2(128.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home54", mHomeAtlas, Vector2(160.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home05", mHomeAtlas, Vector2(0.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home15", mHomeAtlas, Vector2(32.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home25", mHomeAtlas, Vector2(64.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home35", mHomeAtlas, Vector2(96.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home45", mHomeAtlas, Vector2(128.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home55", mHomeAtlas, Vector2(160.0f, 128.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home06", mHomeAtlas, Vector2(0.0f, 160.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home16", mHomeAtlas, Vector2(32.0f, 160.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home26", mHomeAtlas, Vector2(64.0f, 160.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home36", mHomeAtlas, Vector2(96.0f, 160.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home46", mHomeAtlas, Vector2(128.0f, 160.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home56", mHomeAtlas, Vector2(160.0f, 160.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home07", mHomeAtlas, Vector2(0.0f, 192.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home17", mHomeAtlas, Vector2(32.0f, 192.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home27", mHomeAtlas, Vector2(64.0f, 192.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home37", mHomeAtlas, Vector2(96.0f, 192.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home47", mHomeAtlas, Vector2(128.0f, 192.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home57", mHomeAtlas, Vector2(160.0f, 192.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home08", mHomeAtlas, Vector2(0.0f, 224.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home18", mHomeAtlas, Vector2(32.0f, 224.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home28", mHomeAtlas, Vector2(64.0f, 224.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home38", mHomeAtlas, Vector2(96.0f, 224.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home48", mHomeAtlas, Vector2(128.0f, 224.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home58", mHomeAtlas, Vector2(160.0f, 224.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);

			mAnimator->Create(L"Home09", mHomeAtlas, Vector2(0.0f, 256.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home19", mHomeAtlas, Vector2(32.0f, 256.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home29", mHomeAtlas, Vector2(64.0f, 256.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home39", mHomeAtlas, Vector2(96.0f, 256.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home49", mHomeAtlas, Vector2(128.0f, 256.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
			mAnimator->Create(L"Home59", mHomeAtlas, Vector2(160.0f, 256.0f)	,  mTileSize, Vector2::Zero, 1, 0.1f);
		}
	}
}
