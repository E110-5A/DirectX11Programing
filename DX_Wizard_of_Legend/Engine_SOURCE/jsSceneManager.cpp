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

		camTr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		camObj->AddComponent(camTr);
		camObj->AddComponent(camComp);
		camObj->AddComponent(camScript);

		mPlayScene->AddGameObject(camObj, eLayerType::Camera);




		// Rect Obj
		GameObject* rectObj = new GameObject();
		Transform* rectTr = new Transform();
		MeshRenderer* rectMr = new MeshRenderer();
		PlayerScript* rectScript = new PlayerScript();

		rectObj->AddComponent(rectTr);
		rectObj->AddComponent(rectMr);
		rectObj->AddComponent(rectScript);
		
		rectTr->SetPosition(Vector3 (0.0f, 0.0f, 10.0f));
		rectTr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
		rectMr->SetMesh(mesh);
		rectMr->SetMaterial(mateiral);

		std::shared_ptr <Texture> texture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);

		mPlayScene->AddGameObject(rectObj, eLayerType::Player);

		// Sprite Obj
		GameObject* SpriteObj = new GameObject();
		Transform* SpriteTr = new Transform();
		SpriteRenderer* SpriteSr = new SpriteRenderer();

		SpriteObj->AddComponent(SpriteTr);
		SpriteObj->AddComponent(SpriteSr);

		SpriteTr->SetPosition(Vector3(5.0f, 0.0f, 10.0f));

		std::shared_ptr<Material> Spritemateiral = Resources::Find<Material>(L"RectMaterial");
		SpriteSr->SetMesh(mesh);
		SpriteSr->SetMaterial(Spritemateiral);

		mPlayScene->AddGameObject(SpriteObj, eLayerType::Player);
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