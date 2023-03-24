#include "jsPlayScene.h"

#include "jsInput.h"
#include "jsRenderer.h"
#include "jsResources.h"
#include "jsTexture.h"
#include "jsObject.h"

#include "jsTransform.h"

#include "jsCamera.h"
#include "jsCameraScript.h"

#include "jsGridScript.h"

#include "jsMeshRenderer.h"
#include "jsSpriteRenderer.h"
#include "jsFadeScript.h"

#include "jsAnimator.h"

#include "jsPlayer.h"
#include "jsPlayerScript.h"


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
		//Player Obj
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->SetName(L"Player");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			
			Animator* animator = obj->AddComponent<Animator>();
			std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PlayerSpriteSheet", L"Player\\PlayerSpriteSheet.png");
			animator->Create(L"PlayerIdleDown", texture, Vector2(0.0f, 0.0f), Vector2(48.0f, 48.0f), Vector2::Zero, 1, 0.1f);
			animator->Play(L"PlayerIdleDown");


			SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			sr->SetMaterial(Resources::Find<Material>(L"PlayerMaterial"));
			obj->AddComponent<PlayerScript>();
		}


		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			fade->FadeOut();
			fade->SetReady(true);
		}

		if (fade->IsReady() && FadeScript::Complete == fade->GetFadeState())
		{
			fade->SetReady(false);
			fade->SetFadeState(FadeScript::Ready);
			SceneManager::LoadScene(eSceneType::Title);
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
		fade->FadeIn();
	}

	void PlayScene::OnExit()
	{

	}

}
