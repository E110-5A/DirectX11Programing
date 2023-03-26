#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsTransform.h"

namespace js
{
	MeshRenderer::MeshRenderer()
		: BaseRenderer(eComponentType::MeshRenerer)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();

		GetMesh()->Render();

		GetMaterial()->Clear();
	}
}
