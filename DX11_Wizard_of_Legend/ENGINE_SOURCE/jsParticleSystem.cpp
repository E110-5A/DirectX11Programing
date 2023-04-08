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
		, mCount(100)
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
		// Particle CS가져오기
		mCS = Resources::Find<ParticleShader>(L"ParticleCS");

		// material, mesh 세팅
		std::shared_ptr<Material> material = SetMaterial(Resources::Find<Material>(L"ParticleMaterial"));
		SetMesh(Resources::Find<Mesh>(L"PointMesh"));
		material->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"CartoonSmoke"));
		
		// 파티클 전달 데이터 생성
		Particle particles[100] = {};
		Vector4 startPos = Vector4(-800.0f, -450.0f, 0.0f, 0.0f);
		
		// 파티클 개수만큼 세팅
		for (size_t index = 0; index < mCount; index++)
		{
			particles[index].position = Vector4(0.0f, 0.0f, 20.0f, 1.0f);
			particles[index].active = 1;
			particles[index].direction = Vector4( cosf( (float)index * ( XM_2PI / (float)mCount ) ), sin( (float)index * ( XM_2PI / (float)mCount ) ), 0.0f, 1.0f );
			particles[index].speed = 100.0f;
		}

		// 파티클 정보를 구조화버퍼에 담기
		mBuffer = new StructuredBuffer();
		mBuffer->Create(eSRVType::UAV, sizeof(Particle), mCount, particles);
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::FixedUpdate()
	{
		mCS->SetStructedBuffer(mBuffer);
		mCS->OnExcute();
	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::VS, 15);
		mBuffer->BindSRV(eShaderStage::GS, 15);
		mBuffer->BindSRV(eShaderStage::PS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mCount);

		mBuffer->Clear();
	}
}
