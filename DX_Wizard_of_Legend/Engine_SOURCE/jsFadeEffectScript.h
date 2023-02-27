#pragma once
#include "jsScript.h"

namespace js
{
	class FadeEffectScript : public Script
	{
	public:
		enum eFadeState
		{
			Fade_In,
			Fade_Out,
		};
		FadeEffectScript();
		virtual ~FadeEffectScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();


	private:
		bool		isActive;
		float		mAddTime;		// �����ð�
		float		mDuration;		// ȿ�� �ð�
		float		mRatio;
		eFadeState	mType;
	};
}