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
		, mType(Fade_Out)
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
		}

		if (mAddTime >= mDuration)
		{
			isActive = false;
			mAddTime = 0.0f;
		}

		if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::I) && false == isActive
			&& 0.9 <= mRatio)
		{
			isActive = true;
			mType = Fade_In;
		}
		if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::O) && false == isActive
			&& 0.1 >= mRatio)
		{
			isActive = true;
			mType = Fade_Out;
		}
	}
	void FadeEffectScript::FixedUpdate()
	{
		if (!isActive)
			return;

		if (eFadeState::Fade_Out == mType)
		{
			mRatio = (mAddTime / mDuration);
		}
		else if (eFadeState::Fade_In == mType)
		{
			mRatio = 1 - (mAddTime / mDuration);
		}


		// Constant buffer
		ConstantBuffer* FadeEffectCB = renderer::constantBuffers[(UINT)eCBType::FadeEffect];

		renderer::FadeEffectCB data;
		data.alpha = mRatio;

		FadeEffectCB->Bind(&data);
		FadeEffectCB->SetPipline(eShaderStage::PS);
		FadeEffectCB->SetPipline(eShaderStage::VS);
	}
	void FadeEffectScript::Render()
	{
	}
}