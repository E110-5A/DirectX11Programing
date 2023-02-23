#include "jsSceneManager.h"
#include "jsRenderer.h"

#include "jsTransform.h"
#include "jsMeshRenderer.h"

namespace js
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		GameObject* testObj= new GameObject();
		Transform* testTransform = new Transform();
		MeshRenderer* testRenderer = new MeshRenderer();
		
		testObj->AddComponent(testTransform);
		testObj->AddComponent(testRenderer);
		
		testTransform->SetPosition(Vector3(0.2f, 0.2f, 0.0f));
		testRenderer->SetMesh(renderer::mesh);
		testRenderer->SetShader(renderer::shader);


		mPlayScene->AddGameObject(testObj, eLayerType::Player);

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
}