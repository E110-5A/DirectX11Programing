#include "jsTitleScene.h"

#include "jsRenderer.h"
#include "jsInput.h"

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
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;


		//SMILE RECT
		GameObject* obj = object::Instantiate<GameObject>(eLayerType::Player);
		obj->SetName(L"SMILE");
		Transform* tr = obj->GetComponent<Transform>();
		tr->SetPosition(Vector3(0.0f, 0.0f, 5.0f));

		Collider2D* collider = obj->AddComponent<Collider2D>();
		collider->SetType(eColliderType::Rect);

		MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"RectMaterial");
		mr->SetMesh(mesh);
		mr->SetMaterial(mateiral);
		obj->AddComponent<PlayerScript>();
		object::DontDestroyOnLoad(obj);

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
