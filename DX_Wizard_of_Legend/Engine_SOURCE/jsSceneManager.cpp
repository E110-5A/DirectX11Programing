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

#include "jsObject.h"

namespace js
{
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mActiveScene = new Scene();
		

		// Grid Obj
		GameObject* gridObj = object::Instantiate<GameObject>(eLayerType::Grid);
		gridObj->AddComponent<GridScript>();
		MeshRenderer* gridMr = gridObj->AddComponent<MeshRenderer>();
		gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));



		// Main Camera Obj
		GameObject* camObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* camCamera = camObj->AddComponent<Camera>();
		camCamera->TurnLayerMask(eLayerType::UI, false);
		camCamera->RegisterCameraInRenderer();
		CameraScript* camScript = camObj->AddComponent<CameraScript>();		
		



		// UI Camera Obj
		GameObject* UICamObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* UICamCamera = UICamObj->AddComponent<Camera>();
		UICamCamera->DisableLayerMasks();
		UICamCamera->TurnLayerMask(eLayerType::UI);
		UICamCamera->SetProjectionType(Camera::eProjectionType::Orthographic);



		// Smile Obj
		GameObject* smileObj = object::Instantiate<GameObject>(eLayerType::Player, Vector3(0.0f, 0.0f, 9.0f));
		Transform* smileObjTr = smileObj->GetComponent<Transform>();
		smileObj->AddComponent<PlayerScript>();
		MeshRenderer* rectMr = smileObj->AddComponent<MeshRenderer>();
		std::shared_ptr<Mesh> smileMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> rectmaterial = Resources::Find<Material>(L"RectMaterial");
		rectMr->SetMesh(smileMesh);
		rectMr->SetMaterial(rectmaterial);


		// child
		GameObject* child = object::Instantiate<GameObject>(eLayerType::Player, Vector3(2.0f, 0.0f, 0.0f), smileObjTr);
		MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
		std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
		childMr->SetMaterial(childmateiral);
		childMr->SetMesh(smileMesh);


		// Sprite Obj
		GameObject* subObj = object::Instantiate<GameObject>(eLayerType::Player, Vector3(4.0f, 0.0f, 11.0f), Vector3::Zero, Vector3(5.0f, 5.0f, 1.0f));
		SpriteRenderer* subSr = subObj->AddComponent<SpriteRenderer>();		
		std::shared_ptr<Mesh> subMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> subMateiral = Resources::Find<Material>(L"SpriteMaterial");
		subSr->SetMesh(smileMesh);
		subSr->SetMaterial(subMateiral);


		// Light Obj
		GameObject* lightObj = object::Instantiate<GameObject>(eLayerType::Player, Vector3(0.0f, 0.0f, 11.0f), Vector3::Zero, Vector3(5.0f, 5.0f, 1.0f));
		SpriteRenderer* lightSr = lightObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> lightMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> lightMateiral = Resources::Find<Material>(L"LightMaterial");
		lightSr->SetMesh(smileMesh);
		lightSr->SetMaterial(lightMateiral);


		// UI Obj
		GameObject* UIObj = object::Instantiate<GameObject>(eLayerType::UI, Vector3(0.0f, 3.0f, 12.0f), Vector3::Zero, Vector3(10.0f, 10.0f, 1.0f));
		SpriteRenderer* UISr = UIObj->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> uiMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> uiMaterial = Resources::Find<Material>(L"UIMaterial");
		UISr->SetMesh(uiMesh);
		UISr->SetMaterial(uiMaterial);


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