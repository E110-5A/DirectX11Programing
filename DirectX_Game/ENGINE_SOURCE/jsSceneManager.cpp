#include "jsSceneManager.h"

// core
#include "jsRenderer.h"

// component
#include "jsTransform.h"
#include "jsMeshRenderer.h"

// resource
#include "jsResources.h"
#include "jsTexture.h"


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
		Mesh* mesh = Resources::Find<Mesh>(L"RectMesh");
		Shader* shader = Resources::Find<Shader>(L"RectShader");

		testObj->AddComponent(testTransform);
		testObj->AddComponent(testRenderer);
		testTransform->SetPosition(Vector3(0.2f, 0.2f, 0.0f));
		testRenderer->SetMesh(mesh);
		testRenderer->SetShader(shader);

		mPlayScene->AddGameObject(testObj, eLayerType::Player);


		Texture* testTexture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		testTexture->BindShader(eShaderStage::PS, 0);
		
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