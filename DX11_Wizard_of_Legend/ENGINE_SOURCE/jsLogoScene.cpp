#include "jsLogoScene.h"

#include "jsTime.h"
#include "jsInput.h"

#include "jsRenderer.h"

#include "jsObject.h"
#include "jsResources.h"

#include "jsGameObject.h"
#include "jsCamera.h"
#include "jsCameraScript.h"
#include "jsMouseScript.h"

#include "jsMeshRenderer.h"

namespace js
{
	LogoScene::LogoScene()
		: Scene(eSceneType::Title)
		, mBegin(true)
		, mAddTime(0.0f)
	{
	}
	LogoScene::~LogoScene()
	{
	}
	void LogoScene::Initialize()
	{

		// Main Camera
		{
			GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			cameraObj->SetName(L"MainCamObj");
			Camera* cameraComp = cameraObj->AddComponent<Camera>();
			cameraComp->SetName(L"MainCamera");
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			cameraComp->SetProjectionType(Camera::Orthographic);
			cameraObj->AddComponent<CameraScript>();
			object::DontDestroyOnLoad(cameraObj);
			mainCamera = cameraComp;
		}

		// Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::None);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetLightType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			object::DontDestroyOnLoad(directionalLight);
		}

		// Mouse Pointer Obj
		{
			GameObject* mouseObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			mouseObj->SetName(L"MouseObject");
			Transform* mouseTr = mouseObj->GetComponent<Transform>();

			MeshRenderer* mouseMr = mouseObj->AddComponent<MeshRenderer>();
			mouseMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mouseMr->SetMaterial(Resources::Find<Material>(L"MouseMaterial"));
			object::DontDestroyOnLoad(mouseObj);
			MouseScript* mouseScript = mouseObj->AddComponent<MouseScript>();
		}


		// UI Cam
		{
			GameObject* uiCamObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
			uiCamObj->SetName(L"UICamObj");
			Camera* uiCamCamera = uiCamObj->AddComponent<Camera>();
			uiCamCamera->SetName(L"UICamera");
			uiCamCamera->DisableLayerMasks();
			uiCamCamera->TurnLayerMask(eLayerType::UI);
			uiCamCamera->SetProjectionType(Camera::Orthographic);
			uiCamObj->AddComponent<CameraScript>();
			object::DontDestroyOnLoad(uiCamObj);
		}

		//// Fade Obj
		//{
		//	GameObject* fadeObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		//	fadeObj->SetName(L"FadeObject");
		//	Transform* fadeTr = fadeObj->GetComponent<Transform>();
		//	fadeTr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

		//	MeshRenderer* fadeMr = fadeObj->AddComponent<MeshRenderer>();
		//	fadeMr->SetName(L"FadeRenderer");
		//	fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));

		//	FadeScript* fadeScript = fadeObj->AddComponent<FadeScript>();
		//	object::DontDestroyOnLoad(fadeObj);
		//	mFadeObject = fadeObj;
		//	fade = fadeScript;
		//}
				
		// Background Obj
		{
			// Logo
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background, this);
			obj->SetName(L"Logo");

			Transform* tr = obj->GetComponent<Transform>();
			tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			MeshRenderer* sr = obj->AddComponent<MeshRenderer>();
			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			sr->SetMaterial(Resources::Find<Material>(L"LogoMaterial"));
		}

		Scene::Initialize();
	}
	void LogoScene::Update()
	{
		//// 시작하면 fadeIn 실행
		//if (mBegin)
		//{
		//	fade->FadeIn();
		//	mBegin = false;
		//}

		//// 2초가 지나면 fadeOut 실행
		//if (2.0f >= mAddTime)
		//	mAddTime += Time::DeltaTime();
		//else if (false == fade->IsReady())
		//{
		//	fade->FadeOut();
		//	fade->SetReady(true);
		//}

		//// FadeOut이 종료될경우
		//if (fade->IsReady() && FadeScript::Complete == fade->GetFadeState())
		//{
		//	fade->SetReady(false);
		//	fade->SetFadeState(FadeScript::Ready);
		//	SceneManager::LoadScene(eSceneType::Title);
		//}
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Title);
		}
		Scene::Update();
	}
	void LogoScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void LogoScene::Render()
	{
		Scene::Render();
	}
	void LogoScene::OnEnter()
	{
	}
	void LogoScene::OnExit()
	{
	}
}
