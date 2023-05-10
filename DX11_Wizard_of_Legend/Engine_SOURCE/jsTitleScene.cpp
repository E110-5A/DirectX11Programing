#include "jsTitleScene.h"

#include "jsRenderer.h"
#include "jsInput.h"

#include "jsResources.h"
#include "jsObject.h"

#include "jsTransform.h"
#include "jsMeshRenderer.h"

#include "jsFadeScript.h"
#include "jsMouseScript.h"

namespace js
{
	TitleScene::TitleScene()
		: Scene(eSceneType::Title)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		
		// Title Obj
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Tile, this);
			obj->SetName(L"Title");

			Transform* tr = obj->GetComponent<Transform>();
			tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			MeshRenderer* sr = obj->AddComponent<MeshRenderer>();
			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			sr->SetMaterial(Resources::Find<Material>(L"TitleMaterial"));
		}
		// Background Obj
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background, this);
			obj->SetName(L"TitleBG");
			
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			MeshRenderer* sr = obj->AddComponent<MeshRenderer>();
			sr->SetName(L"BackgroundRenderer");
			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));			
			sr->SetMaterial(Resources::Find<Material>(L"TitleBGMaterial"));
		}
		
		Scene::Initialize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Home);
		}
		/*if (Input::GetKeyDown(eKeyCode::N))
		{
			fade->FadeOut();
			fade->SetReady(true);
		}

		if (fade->IsReady() && FadeScript::Complete == fade->GetFadeState())
		{
			fade->SetReady(false);
			fade->SetFadeState(FadeScript::Ready);
			SceneManager::LoadScene(eSceneType::Play);
		}*/

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
		//fade->FadeIn();
	}
	void TitleScene::OnExit()
	{
	}
}
