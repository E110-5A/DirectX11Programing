#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsTransform.h"

namespace js
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::Mesh)
		, mMesh(nullptr)
		, mMaterial(nullptr)
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
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		mMaterial->Bind();
		mMesh->BindBuffer();
		mMesh->Render();
	}
}