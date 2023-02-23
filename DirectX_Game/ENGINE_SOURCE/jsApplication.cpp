#include "jsApplication.h"
#include "jsRenderer.h"
#include "jsTime.h"
#include "jsInput.h"

using namespace js::graphics;

namespace js
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Initialize()
	{
		Time::Initialize();
		Input::Initialize();
		renderer::Initialize();
	}
	void Application::Update()
	{
		Time::Update();
		Input::Update();
	}
	void Application::FixedUpdate()
	{
	}
	void Application::Render()
	{
		Time::Render(mHdc);
		graphicDevice->Render();
	}
	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}
	void Application::Release()
	{
	}
	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mHdc = GetDC(mHwnd);
			mWidth = width;
			mHeight = height;

			ValidationMode vaildationMode = ValidationMode::Disabled;
			graphicDevice = std::make_unique<GraphicDevice_DX11>();
			GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}