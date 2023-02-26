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
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initalize();



		// Camera Obj
		GameObject* camObj = new GameObject();

		Transform* camTr = new Transform();
		Camera* camComp = new Camera();
		CameraScript* camScript = new CameraScript();

		camObj->AddComponent(camTr);
		camTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

		camObj->AddComponent(camComp);
		
		camObj->AddComponent(camScript);

		mPlayScene->AddGameObject(camObj, eLayerType::Camera);






		// Rect Obj
		GameObject* smileObj = new GameObject();

		Transform* rectTr = new Transform();
		MeshRenderer* rectMr = new MeshRenderer();
		smileObj->AddComponent(rectTr);
		rectTr->SetPosition(Vector3 (0.0f, 0.0f, 11.0f));
		rectTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		
		smileObj->AddComponent(rectMr);
		std::shared_ptr<Mesh> rectMesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> rectmaterial = Resources::Find<Material>(L"RectMaterial");
		rectMr->SetMesh(rectMesh);
		rectMr->SetMaterial(rectmaterial);
				
		mPlayScene->AddGameObject(smileObj, eLayerType::Player);




		// Sprite Obj
		GameObject* lightObj = new GameObject();
		Transform* SpriteTr = new Transform();
		SpriteRenderer* lightSr = new SpriteRenderer();

		lightObj->AddComponent(SpriteTr);
		SpriteTr->SetPosition(Vector3(0.0f, 3.0f, 9.0f));
		SpriteTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
		
		lightObj->AddComponent(lightSr);
		std::shared_ptr<Material> lightMateiral = Resources::Find<Material>(L"lightMaterial");
		lightSr->SetMesh(rectMesh);
		lightSr->SetMaterial(lightMateiral);

		mPlayScene->AddGameObject(lightObj, eLayerType::Player);


		// Sprite Obj
		GameObject* subObj = new GameObject();
		Transform* subTr = new Transform();
		SpriteRenderer* subSr = new SpriteRenderer();

		subObj->AddComponent(subTr);
		subTr->SetPosition(Vector3(3.0f, 0.0f, 10.0f));
		subTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

		subObj->AddComponent(subSr);
		std::shared_ptr<Material> subMateiral = Resources::Find<Material>(L"SpriteMaterial");
		subSr->SetMesh(rectMesh);
		subSr->SetMaterial(subMateiral);

		mPlayScene->AddGameObject(subObj, eLayerType::Player);
	}

	void SceneManager::Update()
	{
		mPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene->Render();
	}
	void SceneManager::Release()
	{
		delete mPlayScene;
		mPlayScene = nullptr;
	}
}