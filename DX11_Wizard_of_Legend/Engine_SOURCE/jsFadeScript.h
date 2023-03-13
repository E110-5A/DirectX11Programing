#pragma once
#include "jsScript.h"

namespace js
{
	class FadeScript : public Script
	{
	public:
		enum eFadeType
		{
			Fade_In,
			Fade_Out,
		};

		enum eFadeState
		{
			Ready,
			Processing,
			Complete,
			End,
		};

		FadeScript();
		virtual ~FadeScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void FadeIn();
		void FadeOut();
		eFadeState GetFadeState() { return mState; }
		void SetFadeState(eFadeState state) { mState = state; }
		
		bool IsReady() { return mIsReady; }
		void SetReady(bool enable) { mIsReady = enable; }

	private:
		bool		mIsActive;
		bool		mIsReady;
		eFadeState	mState;
		float		mAddTime;		
		float		mDuration;		
		float		mRatio;
		eFadeType	mType;
	};
}