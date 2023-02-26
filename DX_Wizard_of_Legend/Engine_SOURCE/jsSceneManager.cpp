#include "jsSceneManager.h"
#include "jsRenderer.h"

#include "jsResources.h"
#include "jsTexture.h"

#include "jsTransform.h"
#include "jsMeshRenderer.h"
#include "jsPlayerScript.h"
#include "jsCamera.h"
#include "jsCameraScript.h"
#include "jsSpriteRenderer.h"

namespace js
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mActiveScene = new Scene();
		




		// Camera Obj
		GameObject* camObj = new GameObject();

		Transform* camTr = new Transform();
		Camera* camCamera = new Camera();
		CameraScript* camScript = new CameraScript();

		camObj->AddComponent(camTr);
		camTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

		camObj->AddComponent(camCamera);
		camCamera->TurnLayerMask(eLayerType::UI, false);

		camObj->AddComponent(camScript);

		mActiveScene->AddGameObject(camObj, eLayerType::Camera);


		// UI Camera Obj
		GameObject* UICamObj = new GameObject();

		Transform* UICamTr = new Transform();
		Camera* UICamCamera = new Camera();

		UICamObj->AddComponent(UICamTr);
		UICamTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

		UICamObj->AddComponent(UICamCamera);
		UICamCamera->DisableLayerMasks();
		UICamCamera->TurnLayerMask(eLayerType::UI);
		UICamCamera->SetProjectionType(Camera::eProjectionType::Orthographic);

		mActiveScene->AddGameObject(UICamObj, eLayerType::Camera);




		// Smile Obj
		GameObject* smileObj = new GameObject();

		Transform* rectTr = new Transform();
		MeshRenderer* rectMr = new MeshRenderer();
		smileObj->AddComponent(rectTr);
		rectTr->SetPosition(Vector3 (0.0f, 0.0f, 11.0f));
		rectTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		
		smileObj->AddComponent(rectMr);
		std::shared_ptr<Mesh> smileMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> rectmaterial = Resources::Find<Material>(L"RectMaterial");
		rectMr->SetMesh(smileMesh);
		rectMr->SetMaterial(rectmaterial);

		smileObj->SetName(L"Smile");
		mActiveScene->AddGameObject(smileObj, eLayerType::Player);

		// Sprite Obj
		GameObject* subObj = new GameObject();
		Transform* subTr = new Transform();
		SpriteRenderer* subSr = new SpriteRenderer();

		subObj->AddComponent(subTr);
		subTr->SetPosition(Vector3(4.0f, 0.0f, 11.0f));
		subTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

		subObj->AddComponent(subSr);
		std::shared_ptr<Mesh> subMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> subMateiral = Resources::Find<Material>(L"SpriteMaterial");
		subSr->SetMesh(subMesh);
		subSr->SetMaterial(subMateiral);

		subObj->SetName(L"Default");
		mActiveScene->AddGameObject(subObj, eLayerType::Player);


		// Light Obj
		GameObject* lightObj = new GameObject();
		Transform* SpriteTr = new Transform();
		SpriteRenderer* lightSr = new SpriteRenderer();

		lightObj->AddComponent(SpriteTr);
		SpriteTr->SetPosition(Vector3(0.0f, 0.0f, 11.0f));
		SpriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		
		lightObj->AddComponent(lightSr);
		std::shared_ptr<Mesh> lightMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> lightMateiral = Resources::Find<Material>(L"LightMaterial");
		lightSr->SetMesh(lightMesh);
		lightSr->SetMaterial(lightMateiral);


		lightObj->SetName(L"Light");
		mActiveScene->AddGameObject(lightObj, eLayerType::Player);


		// UI Obj
		GameObject* UIObj = new GameObject();
		Transform* UITr = new Transform();
		SpriteRenderer* UISr = new SpriteRenderer();

		UIObj->AddComponent(UITr);
		UITr->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
		UITr->SetScale(Vector3(10.0f, 10.0f, 10.0f));

		UIObj->AddComponent(UISr);
		std::shared_ptr<Mesh> uiMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> uiMaterial = Resources::Find<Material>(L"UIMaterial");

		UISr->SetMesh(uiMesh);
		UISr->SetMaterial(uiMaterial);

		UIObj->SetName(L"HUD");
		mActiveScene->AddGameObject(UIObj, eLayerType::UI);

		mActiveScene->Initalize();
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