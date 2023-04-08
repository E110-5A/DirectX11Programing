#include "jsParticleSystem.h"
#include "jsMaterial.h"
#include "jsMesh.h"
#include "jsResources.h"

#include "jsGameObject.h"
#include "jsTransform.h"

namespace js
{
	ParticleSystem::ParticleSystem()
		: BaseRenderer(eComponentType::ParticleSystem)
		, mBuffer(nullptr)
		, mCS(nullptr)
		, mCount(0)
		, mStartSize(Vector4::Zero)
		, mStartColor(Vector4::Zero)
		, mLifeTime(0.0f)
	{
	}
	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;
	}
	void ParticleSystem::Initialize()
	{
		// material, mesh 세팅
		std::shared_ptr<Material> material = SetMaterial(Resources::Find<Material>(L"ParticleMaterial"));
		SetMesh(Resources::Find<Mesh>(L"PointMesh"));
		material->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"CartoonSmoke"));
		// 파티클 전달 데이터 생성

		Particle particles[256] = {};
		Vector4 startPos = Vector4(-800.0f, -450.0f, 0.0f, 0.0f);

		// 대략 144개 파티클의 위치를 지정해줌
		for (size_t y = 0; y < 9; y++)
		{
			for (size_t x = 0; x < 16; x++)
			{
				particles[16 * y + x].position = startPos
					+ Vector4(x * 100.0f, y * 100.0f, 0.0f, 0.0f);

				particles[16 * y + x].active = 1;
			}
		}

		// 파티클 정보를 구조화버퍼에 담기
		mCount = 144;
		mBuffer = new StructuredBuffer();
		mBuffer->Create(eSRVType::SRV, sizeof(Particle), mCount, particles);
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::FixedUpdate()
	{
	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 15);
		mBuffer->BindSRV(eShaderStage::GS, 15);
		mBuffer->BindSRV(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);
	}
}
