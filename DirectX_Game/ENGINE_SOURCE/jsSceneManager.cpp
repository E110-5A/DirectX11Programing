#include "jsSceneManager.h"
#include "jsTransform.h"


namespace js
{
	Scene* SceneManager::mPlayScene = nullptr;
	void SceneManager::Initialize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initialize();

		GameObject* testObj= new GameObject();
		Transform* testTransform = new Transform();
		testTransform->SetPosition(Vector3(0.2f, 0.2f, 0.0f));
		testObj->AddComponent(testTransform);

		mPlayScene->AddGameObject(testObj, eLayerType::Player);
	}
	void SceneManager::Update()
	{
	}
	void SceneManager::FixedUpdate()
	{
	}
	void SceneManager::Render()
	{
	}
}