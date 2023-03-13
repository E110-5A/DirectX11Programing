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
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraComp->SetProjectionType(Camera::Orthographic);
		cameraObj->AddComponent<CameraScript>();
		cameraObj->DontDestroy(true);
		mainCamera = cameraComp;


		//// UI Cam
		//{
		//	GameObject* uiCamObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		//	Camera* uiCamCamera = uiCamObj->AddComponent<Camera>();
		//	uiCamCamera->DisableLayerMasks();
		//	uiCamCamera->TurnLayerMask(eLayerType::UI);
		//	uiCamCamera->SetProjectionType(Camera::Orthographic);
		//	uiCamObj->AddComponent<CameraScript>();
		//}
		//// Fade Obj
		//{
		//	GameObject* fadeObj = object::Instantiate<GameObject>(eLayerType::UI, this);
		//	fadeObj->SetName(L"FadeObject");
		//	Transform* fadeTr = fadeObj->GetComponent<Transform>();
		//	fadeTr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		//	fadeTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		//	SpriteRenderer* fadeMr = fadeObj->AddComponent<SpriteRenderer>();
		//	fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
		//	fadeObj->AddComponent<FadeScript>();
		//	object::DontDestroyOnLoad(fadeObj);
		//}
		
		// Background Obj
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Player, this);
			obj->SetName(L"TitleBG");
			
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 1.0f));
			tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TitleBGMaterial"));
		}
				

		////SMILE RECT
		//{
		//	Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
		//	obj->SetName(L"Left");

		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));
		//	
		//	Collider2D* collider = obj->AddComponent<Collider2D>();
		//	collider->SetType(eColliderType::Circle);

		//	SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"RectMaterial"));

		//	obj->AddComponent<PlayerScript>();
		//}

		////SMILE RECT
		//{
		//	Player* obj = object::Instantiate<Player>(eLayerType::Monster, this);
		//	obj->SetName(L"Right");
		//	
		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetPosition(Vector3(2.0f, 0.0f, 5.0f));
		//	tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));

		//	Collider2D* collider = obj->AddComponent<Collider2D>();
		//	collider->SetType(eColliderType::Circle);

		//	SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"RectMaterial"));
		//	object::DontDestroyOnLoad(obj);
		//}


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
