#include "jsSpriteRenderer.h"
#include "jsGameObject.h"
#include "jsTransform.h"
#include "jsAnimator.h"

namespace js
{
	SpriteRenderer::SpriteRenderer()
		: BaseRenderer(eComponentType::SpriteRenderer)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::FixedUpdate()
	{
	}

	void SpriteRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();

		// Mesh에서 렌더하기 전에 Animation 텍스쳐 바인딩하기
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
			animator->Binds();

		GetMesh()->Render();

		GetMaterial()->Clear();

		if (animator)
			animator->Clear();
	}

}
