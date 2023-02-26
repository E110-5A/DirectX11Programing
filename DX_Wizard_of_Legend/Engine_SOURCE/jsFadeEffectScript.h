#pragma once
#include "jsScript.h"

namespace js
{
	class FadeEffectScript : public Script
	{
	public:
		FadeEffectScript();
		virtual ~FadeEffectScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void FadeIn();

	private:
		bool	isActive;
		float	mAddTime;		// 누적시간
		float	mDuration;		// 효과 시간
		bool	mFadeIn;
	};
}