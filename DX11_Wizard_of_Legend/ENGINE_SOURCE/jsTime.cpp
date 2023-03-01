#include "jsTime.h"
#include "jsApplication.h"

extern js::Application application;

namespace js
{
    LARGE_INTEGER	Time::mCpuFrequency = {};
    LARGE_INTEGER   Time::mPrevFrequency = {};
    LARGE_INTEGER	Time::mCurFrequency = {};
    float			Time::mDeltaTime = 0.0f;
    float			Time::mOneSecond = 0.0f;

    void Time::Initialize()
    {
        //CPU �� �ʴ� �ݺ��Ǵ� ���ļ��� ���´�.
        QueryPerformanceFrequency(&mCpuFrequency);

        //���α׷��� ������������ CPU Ŭ�� ��
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


        mOneSecond += mDeltaTime;
        if (1.0f < mOneSecond)
        {
            HWND hWnd = application.GetHwnd();

            wchar_t szFloat[50] = {};
            swprintf_s(szFloat, 50, L"DeltaTime : %d", iCount);
            SetWindowText(hWnd, szFloat);

            mOneSecond = 0.f;
            iCount = 0;
        }
    }
}
