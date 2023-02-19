#pragma once
#include "jsEngine.h"

namespace js
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static __forceinline float GetDeltaTime() { return mDeltaTime * mTimeScale; }
		static void SetTimeScale(float scale) { mTimeScale = scale; }

	private:
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;
		static float mTime;
		static float mTimeScale;
	};
}