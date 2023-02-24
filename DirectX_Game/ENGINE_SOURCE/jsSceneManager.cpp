#include "jsSceneManager.h"

// core
#include "jsRenderer.h"

// component
#include "jsTransform.h"
#include "jsMeshRenderer.h"

// resource
#include "jsResources.h"
#include "jsTexture.h"
#include "jsMaterial.h"

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
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		std::shared_ptr<Material> material = Resources::Find<Material>(L"RectMaterial");

		testObj->AddComponent(testTransform);
		testObj->AddComponent(testRenderer);
		testTransform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		testRenderer->SetMesh(mesh.get());
		testRenderer->SetMaterial(material.get());

		mPlayScene->AddGameObject(testObj, eLayerType::Player);


		std::shared_ptr<Texture> testTexture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
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