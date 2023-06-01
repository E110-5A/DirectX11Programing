#include "jsTile.h"
#include "jsConstantBuffer.h"
#include "jsRenderer.h"
#include "jsResources.h"

namespace js
{
	Tile::Tile()
	{
	}
	Tile::~Tile()
	{
	}
	void Tile::Initialize()
	{
		// ���̾� ����
		// ������Ʈ �߰�
		mTransform = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider2D>();
	}
	void Tile::Update()
	{
	}
	void Tile::FixedUpdate()
	{
		BindShader();
	}
	void Tile::Render()
	{
	}
	void Tile::Clear()
	{
		mAtlas = Resources::Find<Texture>(L"HomeTile");
		mColliderType = eTileCollider::Platform;
		mLocation = Vector2::Zero;
		
		mTileSetIndex = Vector2::Zero;
		mTileSize = Vector2(32.0f, 32.0f);
		mAtlasSize = Vector2(192.0f, 320.0f);;
	}
	void Tile::BindShader()
	{
		// �ؽ��ĸ� �������� 12�� ���Կ� ���ε�
		mAtlas->BindShaderResource(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		// ���� ������� �ִϸ��̼��� ������ ������ ����
		renderer::AnimationCB info = {};
		info.animationType = (UINT)eAnimationType::SecondDimension;

		info.leftTop = mTileSetIndex * 32.0f;
		info.spriteSize = mTileSize;
		info.atlasSize = mAtlasSize;
		info.offset = Vector2::Zero;

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}
}
