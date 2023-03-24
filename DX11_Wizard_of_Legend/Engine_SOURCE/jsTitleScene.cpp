#include "jsTitleScene.h"

#include "jsRenderer.h"
#include "jsInput.h"
#include "jsCollisionManager.h"

#include "jsResources.h"
#include "jsTexture.h"
#include "jsObject.h"

#include "jsTransform.h"
#include "jsCamera.h"
#include "jsCollider2D.h"

#include "jsMeshRenderer.h"
#include "jsSpriteRenderer.h"

#include "jsPlayerScript.h"
#include "jsCameraScript.h"
#include "jsGridScript.h"
#include "jsFadeScript.h"

#include "jsPlayer.h"
#include "jsMonster.h"

#include "jsAnimator.h"
#include "jsMouseScript.h"
namespace js
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Title)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		// Main Camera
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		cameraObj->SetName(L"MainCamObj");
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetName(L"MainCamera");
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraComp->SetProjectionType(Camera::Orthographic);
		cameraObj->AddComponent<CameraScript>();
		object::DontDestroyOnLoad(cameraObj);
		mainCamera = cameraComp;
				
		// Directional Light
		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::None);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetLightType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			object::DontDestroyOnLoad(directionalLight);
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

		// Fade Obj
		{
			GameObject* fadeObj = object::Instantiate<GameObject>(eLayerType::UI, this);
			fadeObj->SetName(L"FadeObject");
			Transform* fadeTr = fadeObj->GetComponent<Transform>();
			fadeTr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			MeshRenderer* fadeMr = fadeObj->AddComponent<MeshRenderer>();
			fadeMr->SetName(L"FadeRenderer");
			fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
			
			FadeScript* fadeScript = fadeObj->AddComponent<FadeScript>();
			object::DontDestroyOnLoad(fadeObj);
			mFadeObject = fadeObj;
			fade = fadeScript;
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
		
		// Background Obj
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Tile, this);
			obj->SetName(L"TitleBG");
			
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			MeshRenderer* sr = obj->AddComponent<MeshRenderer>();
			sr->SetName(L"BackgroundRenderer");
			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));			
			sr->SetMaterial(Resources::Find<Material>(L"TitleBGMaterial"));
		}
		

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		
		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		
		if (Input::GetKeyDown(eKeyCode::N))
		{
			fade->FadeOut();
			fade->SetReady(true);
		}

		if (fade->IsReady() && FadeScript::Complete == fade->GetFadeState())
		{
			fade->SetReady(false);
			fade->SetFadeState(FadeScript::Ready);
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
		fade->FadeIn();
	}
	void TitleScene::OnExit()
	{
	}
}
