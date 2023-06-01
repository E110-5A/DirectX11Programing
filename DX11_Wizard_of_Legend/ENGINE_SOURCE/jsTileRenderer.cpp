#include "jsTileRenderer.h"
#include "jsGameObject.h"
#include "GameObjectComponents.h"

#include "jsTile.h"
namespace js
{
	TileRenderer::TileRenderer()
		: BaseRenderer(eComponentType::TileRenderer)
		, mTileInfo{}
	{
	}
	TileRenderer::~TileRenderer()
	{
	}
	void TileRenderer::Initialize()
	{
	}
	void TileRenderer::Update()
	{
	}
	void TileRenderer::FixedUpdate()
	{
	}
	void TileRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();
				
		BindShader();		// ���� ���̴� ���ε�

		GetMesh()->Render();
		GetMaterial()->Clear();

		Clear();			// ���� Ŭ����
	}

	void TileRenderer::Clear()
	{
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Tile];
		renderer::TileCB info = {};

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}
	void TileRenderer::BindShader()
	{
		// �ؽ��ĸ� �������� 12�� ���Կ� ���ε�
		mAtlas->BindShaderResource(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Tile];

		// ���� ������� �ִϸ��̼��� ������ ������ ����
		renderer::TileCB info = {};

		info.tileLT = mTileInfo.tilesetSize;
		info.tileSize = mTileInfo.tileSize;
		info.tilesetSize = mTileInfo.leftTop;

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}
}