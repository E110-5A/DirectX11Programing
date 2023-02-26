#include "jsSceneManager.h"
#include "jsRenderer.h"

#include "jsResources.h"
#include "jsTexture.h"

#include "jsMeshRenderer.h"
#include "jsSpriteRenderer.h"
#include "jsTransform.h"
#include "jsCamera.h"

#include "jsCameraScript.h"
#include "jsPlayerScript.h"
#include "jsGridScript.h"

namespace js
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mActiveScene = new Scene();
		

		// Grid Obj
		GameObject* gridObj = new GameObject();
		Transform* gridTr = new Transform();
		MeshRenderer* gridMr = new MeshRenderer();

		gridObj->AddComponent(gridTr);
		gridObj->AddComponent(new GridScript());
		gridObj->AddComponent(gridMr);
		gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));

		mActiveScene->AddGameObject(gridObj, eLayerType::Grid);


		// Main Camera Obj
		GameObject* camObj = new GameObject();

		Transform* camTr = new Transform();
		Camera* camCamera = new Camera();
		CameraScript* camScript = new CameraScript();

		camObj->AddComponent(camTr);
		camTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

		camObj->AddComponent(camCamera);
		camCamera->TurnLayerMask(eLayerType::UI, false);
		camCamera->RegisterCameraInRenderer();
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
		PlayerScript* smileScript = new PlayerScript();
		smileObj->AddComponent(rectTr);
		rectTr->SetPosition(Vector3 (0.0f, 0.0f, 9.0f));
		rectTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		
		smileObj->AddComponent(rectMr);
		std::shared_ptr<Mesh> smileMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> rectmaterial = Resources::Find<Material>(L"RectMaterial");
		rectMr->SetMesh(smileMesh);
		rectMr->SetMaterial(rectmaterial);

		smileObj->AddComponent(smileScript);

		smileObj->SetName(L"Smile");
		mActiveScene->AddGameObject(smileObj, eLayerType::Player);

		// child
		GameObject* child = new GameObject();
		Transform* childTr = new Transform();
		childTr->SetPosition(Vector3(2.0f, 0.0f, 0.0f));
		childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		child->AddComponent(childTr);
		childTr->SetParent(rectTr);

		MeshRenderer* childMr = new MeshRenderer();
		child->AddComponent(childMr);




		std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");

		childMr->SetMaterial(childmateiral);
		childMr->SetMesh(smileMesh);

		child->SetName(L"child");
		mActiveScene->AddGameObject(child, eLayerType::Player);



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
		subSr->SetMesh(smileMesh);
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
		lightSr->SetMesh(smileMesh);
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