#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsTransform.h"

namespace js
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::Mesh)
		, mMesh(nullptr)
		, mShader(nullptr)
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

		mShader->Binds();
		mMesh->BindBuffer();
		mMesh->Render();
	}
}