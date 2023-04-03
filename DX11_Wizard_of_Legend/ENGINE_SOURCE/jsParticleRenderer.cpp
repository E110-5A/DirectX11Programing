#include "jsParticleRenderer.h"
#include "jsResources.h"
#include "jsMesh.h"
#include "jsMaterial.h"
#include "jsStructuredBuffer.h"
#include "jsGameObject.h"
#include "jsTransform.h"

namespace js
{
	ParticleRenderer::ParticleRenderer()
		: BaseRenderer(eComponentType::ParticleRenderer)
		, mCount(0)
		, mBuffer(nullptr)
		, mStartSize(Vector4::Zero)
		, mEndSize(Vector4::Zero)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mStartLifeTime(0.0f)
	{
		SetMesh(Resources::Find<Mesh>(L"PointMesh"));		
		std::shared_ptr<Material> material = Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);
		std::shared_ptr<Texture> texture = Resources::Find<Texture>(L"CartoonSmoke");
		material->SetTexture(eTextureSlot::T0, texture);

		Particle particles[1000] = {};
		Vector4 startPos = Vector4(-800.0f, -450.0f, 0.0f, 0.0f);
		for (size_t y = 0; y < 9; y++)
		{
			for (size_t x = 0; x < 16; x++)
			{
				particles[16 * y + x].position = startPos + Vector4(x * 100.0f, y * 100.0f, 0.0f, 0.0f);
				particles[16 * y + x].active = 1;
			}
		}
		mCount = 144;
		mBuffer = new StructuredBuffer();
		mBuffer->Create(eSRVType::None, sizeof(Particle), mCount, particles);
	}
	ParticleRenderer::~ParticleRenderer()
	{
		delete mBuffer;
		mBuffer = nullptr;
	}
	void ParticleRenderer::Initialize()
	{
	}
	void ParticleRenderer::Update()
	{
	}
	void ParticleRenderer::FixedUpdate()
	{
	}
	void ParticleRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->Bind(eShaderStage::VS, 15);
		mBuffer->Bind(eShaderStage::GS, 15);
		mBuffer->Bind(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);
	}
}
