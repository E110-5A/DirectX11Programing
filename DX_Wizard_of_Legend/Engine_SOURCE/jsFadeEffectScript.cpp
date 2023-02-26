#include "jsFadeEffectScript.h"
#include "jsRenderer.h"
#include "jsConstantBuffer.h"
#include "jsTime.h"
#include "jsInput.h"

namespace js
{
	FadeEffectScript::FadeEffectScript()
		: isActive(false)
		, mAddTime(0.0f)
		, mDuration(2.5f)
		, mFadeIn(true)
	{
	}
	FadeEffectScript::~FadeEffectScript()
	{
	}
	void FadeEffectScript::Initalize()
	{
	}
	void FadeEffectScript::Update()
	{
		if (isActive)
		{
			mAddTime += Time::DeltaTime();
			FadeIn();
		}

		if (mAddTime >= mDuration)
		{
			isActive = false;
			mAddTime = 0.0f;
		}

		/*if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::I) && false == isActive)
		{
			isActive = true;
			mFadeIn = true;
		}*/
		if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::O) && false == isActive)
		{
			isActive = true;
			mFadeIn = false;
		}
	}
	void FadeEffectScript::FixedUpdate()
	{
	}
	void FadeEffectScript::Render()
	{
	}
	void FadeEffectScript::FadeIn()
	{
		
		// Constant buffer
		ConstantBuffer* FadeEffectCB = renderer::constantBuffers[(UINT)eCBType::FadeEffect];
		renderer::FadeEffectCB data;
		data.addTime = mAddTime;
		data.duration = mDuration;
		data.fadeIn = mFadeIn;

		FadeEffectCB->Bind(&data);
		FadeEffectCB->SetPipline(eShaderStage::PS);
		FadeEffectCB->SetPipline(eShaderStage::VS);
	}
}