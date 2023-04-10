#pragma once
#include "jsBaseRenderer.h"
#include "jsParticleShader.h"

namespace js
{
	enum class eSimulationSpace
	{
		Local,
		World,
	};
	class ParticleSystem : public BaseRenderer
	{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		class StructuredBuffer* mBuffer;
		class StructuredBuffer* mSharedBuffer;

		std::shared_ptr<ParticleShader> mCS;
		renderer::ParticleSystemCB mCBData;

		UINT mMaxParticles;
		eSimulationSpace mSimulationSpace;
		
		Vector4 mStartSize;
		Vector4 mStartColor;
		float mStartSpeed;
		float mRadius;

		float mFrequency;
		float mLifeTime;
		float mDeltaTime;
		float mElapsedTime;
	};
}