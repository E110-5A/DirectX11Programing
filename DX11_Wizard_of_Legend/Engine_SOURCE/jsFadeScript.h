#pragma once
#include "jsScript.h"

namespace js
{
	class FadeScript : public Script
	{
	public:
		enum eFadeState
		{
			Fade_In,
			Fade_Out,
		};
		FadeScript();
		virtual ~FadeScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	private:
		bool		isActive;
		float		mAddTime;		
		float		mDuration;		
		float		mRatio;
		eFadeState	mType;
	};
}