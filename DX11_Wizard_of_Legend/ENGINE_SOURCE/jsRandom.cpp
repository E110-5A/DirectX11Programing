#include "jsRandom.h"
#include "jsConstantBuffer.h"
#include "jsRenderer.h"

namespace js
{
	Random::Random()
	{
	}
	Random::~Random()
	{
	}
	void Random::Initalize()
	{
	}
	void Random::Update()
	{
	}
	void Random::FixedUpdate()
	{
		// Constant buffer
		ConstantBuffer* FadeCB = renderer::constantBuffers[(UINT)eCBType::Fade];


		float random = rand() % 255;
		random = random / 255;
		renderer::RandomCB data;
		data.random = random;

		FadeCB->Bind(&data);
		FadeCB->SetPipline(eShaderStage::VS);
		FadeCB->SetPipline(eShaderStage::PS);
	}
	void Random::Render()
	{
	}
}