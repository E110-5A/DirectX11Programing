﻿#include "jsTime.h"
#include "jsApplication.h"

extern js::Application application;

namespace js
{
    LARGE_INTEGER	Time::mCpuFrequency = {};
    LARGE_INTEGER   Time::mPrevFrequency = {};
    LARGE_INTEGER	Time::mCurFrequency = {};
    float			Time::mDeltaTime = 0.0f;
    float			Time::mAddTime = 0.0f;

    void Time::Initialize()
    {
        //CPU 의 초당 반복되는 주파수를 얻어온다.
        QueryPerformanceFrequency(&mCpuFrequency);

        //프로그램을 시작했을때의 CPU 클럭 수
        QueryPerformanceCounter(&mPrevFrequency);
    }

    void Time::Update()
    {
        QueryPerformanceCounter(&mCurFrequency);

        float differenceInFrequancy 
            = static_cast<float>((mCurFrequency.QuadPart - mPrevFrequency.QuadPart));

        mDeltaTime = differenceInFrequancy / static_cast<float>(mCpuFrequency.QuadPart);
        mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
    }

    void Time::Render(HDC hdc)
    {
        static int iCount = 0;
        ++iCount;

        mAddTime += mDeltaTime;
        if (1.0f < mAddTime)
        {
            HWND hWnd = application.GetHwnd();
            wchar_t szFloat[50] = {};
            swprintf_s(szFloat, 50, L"DeltaTime : %d", iCount);
            SetWindowText(hWnd, szFloat);

            mAddTime = 0.f;
            iCount = 0;
        }
    }
}
