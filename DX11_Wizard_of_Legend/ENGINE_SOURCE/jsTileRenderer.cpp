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

		// Mesh���� �����ϱ� ���� Animation �ؽ��� ���ε��ϱ�
		// Animator ��� Tile ������Ʈ���� �ؽ��� ���ε�?�ϱ�
		Tile* tile = GetOwner()->GetComponent<Tile>();
		if (tile)
			tile->BindShader();

		GetMesh()->Render();

		GetMaterial()->Clear();

		if (animator)
			animator->Clear();
	}
}