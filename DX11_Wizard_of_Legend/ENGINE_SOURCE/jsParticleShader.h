#pragma once
#include "jsComputeShader.h"
#include "jsStructuredBuffer.h"

namespace js::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		virtual ~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetStructedBuffer(StructuredBuffer* buffer);

	private:
		StructuredBuffer* mBuffer;
	};
}