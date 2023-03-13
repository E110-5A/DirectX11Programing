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


namespace js
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Tilte)
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
			fadeTr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			fadeTr->SetScale(Vector3(16.0f, 9.0f, 1.0f));
			SpriteRenderer* fadeMr = fadeObj->AddComponent<SpriteRenderer>();
			fadeMr->SetName(L"FadeRenderer");
			fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
			fadeObj->AddComponent<FadeScript>();
			object::DontDestroyOnLoad(fadeObj);
		}
		
		// Background Obj
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Tile, this);
			obj->SetName(L"TitleBG");
			
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			mr->SetName(L"BackgroundRenderer");
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TitleBGMaterial"));
		}
			

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		
		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
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
	}
	void TitleScene::OnExit()
	{
	}
}
