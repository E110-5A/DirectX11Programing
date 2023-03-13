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

		/*if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::I) && false == mIsActive
			&& 0.9 <= mRatio)
		{
			mIsComplete = false;
			mIsActive = true;
			mType = Fade_In;
		}
		if (eKeyState::PRESSED == Input::GetKeyState(eKeyCode::O) && false == mIsActive
			&& 0.1 >= mRatio)
		{
			mIsComplete = false;
			mIsActive = true;
			mType = Fade_Out;
		}*/
	}

	void FadeScript::FadeIn()
	{
		mIsActive = true;
		mState = eFadeState::Processing;
		mType = Fade_In;
	}
	void FadeScript::FadeOut()
	{
		mIsActive = true;
		mState = eFadeState::Processing;
		mType = Fade_Out;
	}


	void FadeScript::FixedUpdate()
	{
		if (!mIsActive)
			return;

		// alpha test
		if (mRatio > 0.5f)
			int a = 0;

		if (eFadeType::Fade_Out == mType)
		{
			mRatio = (mAddTime / mDuration);
		}
		else if (eFadeType::Fade_In == mType)
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