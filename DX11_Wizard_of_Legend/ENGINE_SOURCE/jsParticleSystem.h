#pragma once
#include "jsBaseRenderer.h"
#include "jsParticleShader.h"

namespace js
{
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
		std::shared_ptr<ParticleShader> mCS;

		UINT mCount;
		Vector4 mStartSize;
		Vector4 mStartColor;
		Vector4 mLifeTime;

	};
}