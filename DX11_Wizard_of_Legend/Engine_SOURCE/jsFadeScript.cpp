#include "jsFadeScript.h"
#include "jsRenderer.h"
#include "jsConstantBuffer.h"
#include "jsTime.h"
#include "jsInput.h"

namespace js
{
	FadeScript::FadeScript()
		: mIsActive(false)
		, mIsReady(false)
		, mState(eFadeState::Ready)
		, mAddTime(0.0f)
		, mDuration(0.5f)
		, mRatio(1.0f)
		, mType(eFadeType::Fade_In)
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
		if (mIsActive)
		{
			mAddTime += Time::DeltaTime();

			if (mAddTime >= mDuration)
			{
				mIsActive = false;
				mState = eFadeState::Complete;
				mAddTime = 0.0f;
			}
		}
	}

	void FadeScript::FadeIn(float duration)
	{
		mIsActive = true;
		mState = eFadeState::Processing;
		mType = Fade_In;
		mDuration = duration;
	}
	void FadeScript::FadeOut(float duration)
	{
		mIsActive = true;
		mState = eFadeState::Processing;
		mType = Fade_Out;
		mDuration = duration;
	}

	void FadeScript::FixedUpdate()
	{
		if (!mIsActive)
			return;

		if (eFadeType::Fade_Out == mType)
			mRatio = (mAddTime / mDuration);
		else if (eFadeType::Fade_In == mType)
			mRatio = 1 - (mAddTime / mDuration);

		// Constant buffer
		ConstantBuffer* FadeCB = renderer::constantBuffers[(UINT)eCBType::Fade];

		renderer::FadeCB data;
		data.alpha = mRatio;

		FadeCB->SetData(&data);
		FadeCB->Bind(eShaderStage::VS);
		FadeCB->Bind(eShaderStage::PS);
	}
	void FadeScript::Render()
	{
	}
}