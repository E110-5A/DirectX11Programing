#include "jsPlayScene.h"

#include "jsInput.h"
#include "jsRenderer.h"
#include "jsResources.h"
#include "jsObject.h"

#include "jsCollisionManager.h"

#include "jsCamera.h"
#include "jsCameraScript.h"

#include "jsMeshRenderer.h"
#include "jsGridScript.h"
#include "jsFadeScript.h"

#include "jsSpriteRenderer.h"
#include "jsTransform.h"

#include "jsAnimator.h"

#include "jsPlayer.h"
#include "jsPlayerScript.h"
#include "jsRigidbody.h"
#include "jsArcanaScript.h"

#include "jsMonsterScript.h"

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
		//Player Obj & Projectile Obj Pool
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player, this);
			obj->OnPause();
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
			renderer::player = playerScript;

			std::vector<Script*> camScripts = renderer::mainCameraObject->GetScripts();
			CameraScript* cameraScript = dynamic_cast<CameraScript*>(camScripts[0]);

			if (nullptr != cameraScript)
			{
				cameraScript->SetCamFollow(obj);
			}

			// 투사체 생성
			for (int index = 0; index < PROJECTILE_POOL; ++index)
			{
				GameObject* projecObj = object::Instantiate<GameObject>(eLayerType::PlayerProjectile, this);
				projecObj->OnPause();
				projecObj->SetName(L"projectile");
				projecObj->AddComponent<Collider2D>();
				projecObj->AddComponent<Animator>();
				projecObj->AddComponent<Rigidbody>();
				SpriteRenderer* projecSr = projecObj->AddComponent<SpriteRenderer>();
				projecSr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				projecSr->SetMaterial(Resources::Find<Material>(L"ObjectMaterial"));
				ArcanaScript* arcana = projecObj->AddComponent<ArcanaScript>();
				playerScript->AddProjectile(arcana);
				playerScript->SetProjectileID(index);
			}
		}
		
		// Monster
		{
			GameObject* monsterObj = object::Instantiate<GameObject>(eLayerType::Monster, this);
			monsterObj->SetName(L"monster");
			monsterObj->AddComponent<Collider2D>();
			monsterObj->AddComponent<Animator>();
			monsterObj->AddComponent<Rigidbody>();

			Transform* tr = monsterObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 0.0f, 1.0f));

			SpriteRenderer* sr = monsterObj->AddComponent<SpriteRenderer>();
			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			sr->SetMaterial(Resources::Find<Material>(L"ObjectMaterial"));
			monsterObj->AddComponent<MonsterScript>();

		}

		// Skill & Health HUD
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

		// Temp Background Tile
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background, this);
			obj->SetName(L"PlayBG");

			Transform* tr = obj->GetComponent<Transform>();
			tr->SetScale(Vector3(16.0f, 9.0f, 1.0f));

			MeshRenderer* sr = obj->AddComponent<MeshRenderer>();
			sr->SetName(L"BackgroundRenderer");
			sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			sr->SetMaterial(Resources::Find<Material>(L"BGMaterial"));
			std::shared_ptr<Material> BGMaterial = sr->GetMaterial();
			BGMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"PlayBackGround"));
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
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::PlayerProjectile);
		renderer::player->GetOwner()->OnActive();
	}

	void PlayScene::OnExit()
	{

	}

}
