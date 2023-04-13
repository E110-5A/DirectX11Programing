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
#include "jsRigidbody.h"
#include "jsArcanaScript.h"

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
			obj->AddComponent<Collider2D>();
			obj->AddComponent<Animator>();
			obj->AddComponent<Rigidbody>();

			SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			sr->SetMaterial(Resources::Find<Material>(L"ObjectMaterial"));
			PlayerScript* playerScript = obj->AddComponent<PlayerScript>();


			GameObject* projecObj = object::Instantiate<GameObject>(eLayerType::Projectile, this);
			projecObj->SetName(L"projectile");
			projecObj->AddComponent<Collider2D>();
			projecObj->AddComponent<Animator>();
			SpriteRenderer* projecSr = projecObj->AddComponent<SpriteRenderer>();
			projecSr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			projecSr->SetMaterial(Resources::Find<Material>(L"ObjectMaterial"));
			ArcanaScript* arcana = projecObj->AddComponent<ArcanaScript>();
			projecObj->AddComponent<Rigidbody>();
			playerScript->SetProjectile(arcana);

			for (int index = 0; index < PROJECTILE_POOL; ++index)
			{
				// 투사체 생성
				GameObject* projecObj = object::Instantiate<GameObject>(eLayerType::Projectile, this);
				projecObj->SetName(L"projectile");
				projecObj->AddComponent<Collider2D>();
				projecObj->AddComponent<Animator>();
				projecObj->AddComponent<Rigidbody>();
				SpriteRenderer* projecSr = projecObj->AddComponent<SpriteRenderer>();
				projecSr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				projecSr->SetMaterial(Resources::Find<Material>(L"ObjectMaterial"));
				// 스크립트 추가
				ArcanaScript* arcana = projecObj->AddComponent<ArcanaScript>();
				playerScript->AddProjectile(arcana);
			}
		}
			
		// HUD
		{
			GameObject* healthHUD = object::Instantiate<Player>(eLayerType::UI, this);
			healthHUD->SetName(L"HealthHUD");
			Transform* healthTr = healthHUD->GetComponent<Transform>();
			healthTr->SetPosition(Vector3(-3.3f, 3.8f, 1.0f));
			healthTr->SetScale(Vector3(3.4f, 1.0f, 1.0f));
			MeshRenderer* healthMr = healthHUD->AddComponent<MeshRenderer>();
			healthMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			healthMr->SetMaterial(Resources::Find<Material>(L"HealthHUDMaterial"));

			GameObject* skillHUD = object::Instantiate<Player>(eLayerType::UI, this);
			skillHUD->SetName(L"SkillHUD");
			Transform* skillTr = skillHUD->GetComponent<Transform>();
			skillTr->SetPosition(Vector3(-3.3f, -2.5f, 1.0f));
			skillTr->SetScale(Vector3(3.0f, 1.0f, 1.0f));

			MeshRenderer* skillMr = skillHUD->AddComponent<MeshRenderer>();
			skillMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			skillMr->SetMaterial(Resources::Find<Material>(L"SkillHUDMaterial"));
		}

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		/*if (Input::GetKeyDown(eKeyCode::N))
		{
			fade->FadeOut();
			fade->SetReady(true);
		}

		if (fade->IsReady() && FadeScript::Complete == fade->GetFadeState())
		{
			fade->SetReady(false);
			fade->SetFadeState(FadeScript::Ready);
			SceneManager::LoadScene(eSceneType::Title);
		}*/

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
		//fade->FadeIn();
	}

	void PlayScene::OnExit()
	{

	}

}
