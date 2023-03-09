#include "jsFadeScript.h"
#include "jsRenderer.h"
#include "jsConstantBuffer.h"
#include "jsTime.h"
#include "jsInput.h"

namespace js
{
	FadeScript::FadeScript()
		: isActive(false)
		, mAddTime(0.0f)
		, mDuration(1.5f)
		, mRatio(0.0f)
		, mType(eFadeState::Fade_In)
	{	
	}
	FadeScript::~FadeScript()
	{
	}

	void FadeScript::Initalize()
	{
	}
	void FadeScript::Update()
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
	void FadeScript::FixedUpdate()
	{
		if (!isActive)
			return;

		// alpha test
		if (mRatio > 0.5f)
			int a = 0;

		if (eFadeState::Fade_Out == mType)
		{
			mRatio = (mAddTime / mDuration);
		}
		else if (eFadeState::Fade_In == mType)
		{
			mRatio = 1 - (mAddTime / mDuration);
		}


		// Constant buffer
		ConstantBuffer* FadeCB = renderer::constantBuffers[(UINT)eCBType::Fade];

		renderer::FadeCB data;
		data.alpha = mRatio;

		FadeCB->Bind(&data);
		FadeCB->SetPipline(eShaderStage::VS);
		FadeCB->SetPipline(eShaderStage::PS);
	}
	void FadeScript::Render()
	{
	}
}