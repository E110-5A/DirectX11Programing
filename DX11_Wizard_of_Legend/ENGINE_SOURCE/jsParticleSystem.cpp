#include "jsParticleSystem.h"
#include "jsMaterial.h"
#include "jsMesh.h"
#include "jsResources.h"

#include "jsGameObject.h"
#include "jsTransform.h"
#include "jsTime.h"

namespace js
{
	ParticleSystem::ParticleSystem()
		: BaseRenderer(eComponentType::ParticleSystem)
		, mBuffer(nullptr)
		, mSharedBuffer(nullptr)
		, mCS(nullptr)
		, mCBData{}
		, mMaxParticles(100)
		, mSimulationSpace(eSimulationSpace::World)
		, mStartSize(Vector4(50.0f, 50.0f, 1.0f, 1.0f))
		, mStartColor(Vector4(0.2f, 1.0f, 1.0f, 1.0f))
		, mStartSpeed(200.0f)
		, mRadius(500.0f)
		, mFrequency(1.0f)
		, mLifeTime(3.0f)
		, mDeltaTime(0.0f)
		, mElapsedTime(0.0f)
	{
	}
	ParticleSystem::~ParticleSystem()
	{
		delete mBuffer;
		mBuffer = nullptr;
		delete mSharedBuffer;
		mSharedBuffer = nullptr;
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
		Vector4 startPos = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		
		// 파티클 개수만큼 세팅
		for (size_t index = 0; index < mMaxParticles; index++)
		{
			particles[index].position = Vector4(0.0f, 0.0f, 20.0f, 1.0f);
			particles[index].active = 0;
			particles[index].direction = Vector4( cosf( (float)index * ( XM_2PI / (float)mMaxParticles) )
												, sin( (float)index * ( XM_2PI / (float)mMaxParticles) ), 0.0f, 1.0f );
			particles[index].speed = 100.0f;
		}

		// 파티클 정보를 구조화버퍼에 담기
		mBuffer = new StructuredBuffer();
		mBuffer->Create(eSRVType::UAV, sizeof(Particle), mMaxParticles, particles);

		mSharedBuffer = new StructuredBuffer();
		mSharedBuffer->Create(eSRVType::UAV, sizeof(ParticleShared), 1, nullptr, true);
	}
	void ParticleSystem::Update()
	{
	}
	void ParticleSystem::FixedUpdate()
	{
		// 파티클 생성시간
		float aliveTime = 1.0f / mFrequency;

		mElapsedTime += Time::DeltaTime();

		//
		if (aliveTime < mElapsedTime)
		{
			float f = (mElapsedTime / aliveTime);
			UINT iAliveCount = (UINT)f;
			mElapsedTime = f - std::floor(f);

			ParticleShared shared = { 5 };
			mSharedBuffer->SetData(&shared, 1);
		}
		else
		{
			ParticleShared shared = {};
			mSharedBuffer->SetData(&shared, 1);
		}

		mMaxParticles = mBuffer->GetStride();
		Vector3 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		
		mCBData.worldPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mCBData.color = mStartColor;
		mCBData.size = mStartSize;
		
		mCBData.maxParticles = mMaxParticles;
		mCBData.simulationSpace = (UINT)mSimulationSpace;
		mCBData.radius = mRadius;
		mCBData.speed = mStartSpeed;

		mCBData.lifeTime = mLifeTime;
		mCBData.deltaTime = Time::DeltaTime();
		mCBData.elapsedTime = mElapsedTime;


		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleSystem];
		cb->SetData(&mCBData);
		cb->Bind(eShaderStage::ALL);

		mCS->SetStructedBuffer(mBuffer);
		mCS->SetSharedStructedBuffer(mSharedBuffer);
		mCS->OnExcute();
	}
	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->BindSRV(eShaderStage::GS, 15);

		GetMaterial()->Bind();
		GetMesh()->RenderInstanced(mMaxParticles);

		mBuffer->Clear();
	}
}
