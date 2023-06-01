#include "jsTileRenderer.h"
#include "jsGameObject.h"
#include "GameObjectComponents.h"

#include "jsTile.h"
namespace js
{
	TileRenderer::TileRenderer()
		: BaseRenderer(eComponentType::TileRenderer)
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

		// Mesh에서 렌더하기 전에 Animation 텍스쳐 바인딩하기
		// Animator 대신 Tile 컴포넌트에서 텍스쳐 바인딩?하기
		Tile* tile = GetOwner()->GetComponent<Tile>();
		if (tile)
			tile->BindShader();

		GetMesh()->Render();

		GetMaterial()->Clear();

		if (animator)
			animator->Clear();
	}
}