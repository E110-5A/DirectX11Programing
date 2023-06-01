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
				
		BindShader();		// 셀프 셰이더 바인딩

		GetMesh()->Render();
		GetMaterial()->Clear();

		Clear();			// 셀프 클리어
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
		// 텍스쳐를 레지스터 12번 슬롯에 바인딩
		mAtlas->BindShaderResource(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Tile];

		// 현재 재생중인 애니메이션의 프레임 정보를 전달
		renderer::TileCB info = {};

		info.tileLT = mTileInfo.tilesetSize;
		info.tileSize = mTileInfo.tileSize;
		info.tilesetSize = mTileInfo.leftTop;

		cb->SetData(&info);
		cb->Bind(eShaderStage::PS);
	}
}