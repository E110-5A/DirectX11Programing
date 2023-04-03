#pragma once
#include "jsBaseRenderer.h"

namespace js
{
	class ParticleRenderer : public BaseRenderer
	{
	public:
		ParticleRenderer();
		virtual ~ParticleRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	private:
		class StructuredBuffer* mBuffer;

		UINT mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float	mStartLifeTime;
	};
}