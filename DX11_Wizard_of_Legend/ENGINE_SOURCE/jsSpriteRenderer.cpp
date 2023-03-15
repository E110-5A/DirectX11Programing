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

		// Mesh���� �����ϱ� ���� Animation �ؽ��� ���ε��ϱ�
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (animator)
			animator->Binds();

		GetMesh()->Render();

		GetMaterial()->Clear();

		if (animator)
			animator->Clear();
	}

}
