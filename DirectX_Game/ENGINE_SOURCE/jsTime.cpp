#include "jsTime.h"
#include "jsApplication.h"

extern js::Application application;

namespace js
{
	LARGE_INTEGER	Time::mCpuFrequency = {};
	LARGE_INTEGER	Time::mPrevFrequency = {};
	LARGE_INTEGER	Time::mCurFrequency = {};
	float			Time::mDeltaTime = 0.f;
	float			Time::mTime = 0.f;
	float			Time::mTimeScale = 1.0f;


	void Time::Initialize()
	{
		QueryPerformanceFrequency(&mCpuFrequency);
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float fFrequencyGab
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = fFrequencyGab / static_cast<float>(mCpuFrequency.QuadPart);
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	// 호출안함
	void Time::Render(HDC _dc)
	{
		static int iCount = 0;
		++iCount;
		mTime += mDeltaTime;

		if (1.0f < mTime)
		{
			HWND hWnd = application.GetHwnd();
			wchar_t szFloat[30] = {};
			swprintf_s(szFloat, 30, L"Delta Time : %d", iCount);
			SetWindowText(hWnd, szFloat);

			mTime = 0.f;
			iCount = 0;
		}
	}
}