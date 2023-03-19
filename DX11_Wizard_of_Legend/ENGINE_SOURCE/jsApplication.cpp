#include "jsApplication.h"
#include "jsRenderer.h"
#include "jsTime.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsResources.h"
#include "jsCollisionManager.h"
namespace js
{
	using namespace graphics;

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
		CollisionManager::Initialize();

		renderer::Initialize();
		SceneManager::Initialize();
	}

	// ���� ���� ĳ���� �̵� ��� 
	// CPU UPDATE
	void Application::Update()
	{
		Time::Update();
		Input::Update();

		CollisionManager::Update();
		SceneManager::Update();
	}

	// GPU update
	void Application::FixedUpdate()
	{
		CollisionManager::FixedUpdate();
		SceneManager::FixedUpdate();
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		graphicDevice->Clear();
		graphicDevice->AdjustViewPorts();

		renderer::Render();
		CollisionManager::Render();
	}

	void Application::Destroy()
	{

	}

	// Running main engine loop
	void Application::Run()
	{
		Update();
		FixedUpdate();
		Render();
		Destroy();
	}

	void Application::Release()
	{
		Resources::deleteTest();
	}

	void Application::Pressent()
	{
		graphicDevice->Present();
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
			graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}