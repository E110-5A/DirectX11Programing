#include "jsParticleShader.h"
#include "jsRenderer.h"
#include "jsConstantBuffer.h"
#include "jsTime.h"

namespace js::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, mBuffer(nullptr)
	{
	}
	ParticleShader::~ParticleShader()
	{
	}
	void ParticleShader::Binds()
	{
		mBuffer->BindUAV(eShaderStage::CS, 0);

		mGroupX = mBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}
	void ParticleShader::Clear()
	{
		mBuffer->Clear();
	}
	void ParticleShader::SetStructedBuffer(StructuredBuffer* buffer)
	{
		mBuffer = buffer;

		renderer::ParticleRendererCB info = {};
		info.elementCount = mBuffer->GetStride();
		info.deltaTime = Time::DeltaTime();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::ParticleRenderer];
		cb->SetData(&info);
		cb->Bind(eShaderStage::CS);
	}
}
