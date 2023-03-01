#include "jsSceneManager.h"
#include "jsRenderer.h"

#include "jsResources.h"
#include "jsTexture.h"
#include "jsObject.h"

#include "jsTransform.h"
#include "jsCamera.h"
#include "jsMeshRenderer.h"
#include "jsSpriteRenderer.h"

#include "jsCameraScript.h"
#include "jsPlayerScript.h"
#include "jsGridScript.h"
#include "jsFadeEffectScript.h"

namespace js
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mActiveScene = new Scene();

		// Grid Object
		GameObject* gridObj = object::Instantiate<GameObject>(eLayerType::Grid);
		gridObj->AddComponent<GridScript>();
		MeshRenderer* gridMr = gridObj->AddComponent<MeshRenderer>();
		gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));

		// Main Camera Game Object
		GameObject* camObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* camCamera = camObj->AddComponent<Camera>();
		camCamera->RegisterCameraInRenderer();
		camCamera->TurnLayerMask(eLayerType::UI, false);
		camObj->AddComponent<CameraScript>();

		// UI Camera
		GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		cameraUIComp->DisableLayerMasks();
		cameraUIComp->TurnLayerMask(eLayerType::UI, true);
		cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);

		// Light Object
		GameObject* lightObj = object::Instantiate<GameObject>(eLayerType::Player, Vector3(0.0f, 0.0f, 11.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(5.0f, 5.0f, 1.0f));
		SpriteRenderer* sr = lightObj->AddComponent<SpriteRenderer>();
		sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		sr->SetMaterial(Resources::Find<Material>(L"LightMaterial"));


		//SMILE RECT
		GameObject* smileObj = object::Instantiate<GameObject>(eLayerType::Player, Vector3(-3.0f, 0.0f, 11.0f), Vector3(0.0f, 0.0f, XM_PIDIV2));
		Transform* smileTr = smileObj->GetComponent<Transform>();
		smileObj->AddComponent<PlayerScript>();
		MeshRenderer* smileMr = smileObj->AddComponent<MeshRenderer>();
		std::shared_ptr<Material> smileMateiral = Resources::Find<Material>(L"SmileMaterial");
		smileMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		smileMr->SetMaterial(smileMateiral);

		//SMILE RECT CHild
		GameObject* childObj = object::Instantiate<GameObject>(eLayerType::Player, Vector3(2.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), smileTr);
		MeshRenderer* childMr = childObj->AddComponent<MeshRenderer>();
		childMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		childMr->SetMaterial(Resources::Find<Material>(L"SmileMaterial"));

		// HUD
		GameObject* UIObj = object::Instantiate<GameObject>(eLayerType::UI, Vector3(0.0f, 3.0f, 12.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 1.0f));
		SpriteRenderer* UISr = UIObj->AddComponent<SpriteRenderer>();
		UIObj->AddComponent(UISr);
		UISr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		UISr->SetMaterial(Resources::Find<Material>(L"UIMaterial"));

		// FadeEffect Obj
		GameObject* fadeEffectObj = object::Instantiate<GameObject>(eLayerType::Effect, Vector3::Zero, Vector3::Zero, Vector3(100.0f, 100.0f, 1.0f));
		SpriteRenderer* fadeEffectSr = fadeEffectObj->AddComponent<SpriteRenderer>();
		fadeEffectSr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		fadeEffectSr->SetMaterial(Resources::Find<Material>(L"FadeEffectMaterial"));
		fadeEffectObj->AddComponent<FadeEffectScript>();

		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	void SceneManager::Release()
	{
		delete mActiveScene;
		mActiveScene = nullptr;
	}
}