#include "jsPlayScene.h"
#include "jsTransform.h"
#include "jsMeshRenderer.h"
#include "jsRenderer.h"
#include "jsResources.h"
#include "jsTexture.h"
#include "jsPlayerScript.h"
#include "jsCamera.h"
#include "jsCameraScript.h"
#include "jsSpriteRenderer.h"
#include "jsGridScript.h"
#include "jsObject.h"
#include "jsInput.h"

namespace js
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{
		
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Tilte);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{

	}

	void PlayScene::OnExit()
	{

	}

}
