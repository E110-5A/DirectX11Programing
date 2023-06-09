#include "jsHomeScene.h"

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

#include "jsLight.h"

#include "GameObjectsAndScripts.h"

namespace js
{
	HomeScene::HomeScene()
		: Scene(eSceneType::Home)
	{
		
	}

	HomeScene::~HomeScene()
	{
	}

	void HomeScene::Initialize()
	{
		//Player Obj & Projectile Obj Pool
		{
			Player* obj = object::InstantiateGameObject<Player>(eLayerType::Player, this);
			obj->OnPause();
			obj->SetName(L"Player");
			Transform* objTr = obj->GetComponent<Transform>();
			
			objTr->SetScale(Vector3(2.0f, 2.0f, 1.0f));

			// 카메라 관련 예외처리
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
				GameObject* projecObj = object::InstantiateGameObject<GameObject>(eLayerType::PlayerProjectile, this);
				projecObj->OnPause();
				projecObj->SetName(L"projectile");
				Transform* projecTr = projecObj->GetComponent<Transform>(); 
				ArcanaScript* arcana = projecObj->AddComponent<ArcanaScript>();
				playerScript->AddProjectile(arcana);
				playerScript->SetProjectileID(index);
			}
		}
		
		// Monster & Projectile Obj
		{
			GameObject* monsterObj = object::InstantiateGameObject<GameObject>(eLayerType::Monster, this);
			monsterObj->SetName(L"monster");
			Transform* tr = monsterObj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 0.0f, 1.0f));
			monsterObj->AddComponent<MonsterScript>();

			GameObject* projecObj = object::InstantiateGameObject<GameObject>(eLayerType::MonsterProjectile, this);
			projecObj->SetName(L"P_Mon");
			Transform* projecTr = projecObj->GetComponent<Transform>();
			projecTr->SetPosition(Vector3(-3.0f, 2.5f, 1.0f));
			ProjectileScript* testScript = projecObj->AddComponent<ProjectileScript>();
			testScript->TurnTest();
		}

		// Skill & Health HUD
		{
			GameObject* healthHUD = object::Instantiate<GameObject>(eLayerType::UI, this);
			healthHUD->SetName(L"HealthHUD");
			Transform* healthTr = healthHUD->GetComponent<Transform>();
			healthTr->SetPosition(Vector3(-3.3f, 3.8f, 1.0f));
			healthTr->SetScale(Vector3(3.4f, 1.0f, 1.0f));
			MeshRenderer* healthMr = healthHUD->AddComponent<MeshRenderer>();
			healthMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			healthMr->SetMaterial(Resources::Find<Material>(L"HealthHUDMaterial"));

			GameObject* skillHUD = object::Instantiate<GameObject>(eLayerType::UI, this);
			skillHUD->SetName(L"SkillHUD");
			Transform* skillTr = skillHUD->GetComponent<Transform>();
			skillTr->SetPosition(Vector3(-3.3f, -2.5f, 1.0f));
			skillTr->SetScale(Vector3(3.0f, 1.0f, 1.0f));

			MeshRenderer* skillMr = skillHUD->AddComponent<MeshRenderer>();
			skillMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			skillMr->SetMaterial(Resources::Find<Material>(L"SkillHUDMaterial"));
		}

		//// Temp Background Tile
		//{
		//	GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background, this);
		//	obj->SetName(L"Background");

		//	Transform* tr = obj->GetComponent<Transform>();
		//	tr->SetScale(Vector3(77.6f, 77.6f, 1.0f) * 0.3f);

		//	MeshRenderer* sr = obj->AddComponent<MeshRenderer>();
		//	sr->SetName(L"BackgroundRenderer");
		//	sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	sr->SetMaterial(Resources::Find<Material>(L"BGMaterial"));
		//	std::shared_ptr<Material> BGMaterial = sr->GetMaterial();
		//	BGMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"HomeStage"));

		//	mAnimator->Create(L"Home00", mHomeAtlas, Vector2(0.0f, 0.0f)		, mTileSize, Vector2::Zero, 1, 0.1f);
		//	mAnimator->Create(L"Home10", mHomeAtlas, Vector2(32.0f, 0.0f)		, mTileSize, Vector2::Zero, 1, 0.1f);
		//}

		// renderTest Object
		/*{
			GameObject obj = object::InstantiateGameObject<GameObject>()
		}*/

		// temp Lights test
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Background, this);
			obj->SetName(L"testLight");
			Light* light = obj->AddComponent<Light>();
			light->SetLightType(eLightType::Point);
			light->SetRadius(15.0f);
			light->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			light->SetAmbient(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		}

		SceneManager::SetMapSize(eSceneType::Home, Vector2(14.0f, 16.0f), this);
		SceneManager::EditTileToRoom(eSceneType::Home, Vector2(0.0f, 0.0f), Vector2(14.0f, 9.0f), eTileSet::Home);

		//{
		//	// left
		//	SceneManager::EditTile(eSceneType::Home, Vector2(0.0f, 3.0f), Vector2(0.0f, 3.0f), eTileCollider::Wall, Vector2(0.0f, 5.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(0.0f, 2.0f), Vector2(0.0f, 2.0f), eTileCollider::Wall, Vector2(0.0f, 1.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(0.0f, 1.0f), Vector2(0.0f, 1.0f), eTileCollider::Wall, Vector2(0.0f, 1.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), eTileCollider::Wall, Vector2(0.0f, 4.0f));

		//	// middle
		//	SceneManager::EditTile(eSceneType::Home, Vector2(1.0f, 3.0f), Vector2(1.0f, 3.0f), eTileCollider::Wall, Vector2(1.0f, 3.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(1.0f, 2.0f), Vector2(1.0f, 2.0f), eTileCollider::Wall, Vector2(2.0f, 1.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(1.0f, 1.0f), Vector2(1.0f, 1.0f), eTileCollider::Platform, Vector2(2.0f, 4.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(1.0f, 0.0f), Vector2(1.0f, 0.0f), eTileCollider::Wall, Vector2(0.0f, 3.0f));

		//	// right
		//	SceneManager::EditTile(eSceneType::Home, Vector2(2.0f, 3.0f), Vector2(2.0f, 3.0f), eTileCollider::Wall, Vector2(1.0f, 5.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(2.0f, 2.0f), Vector2(2.0f, 2.0f), eTileCollider::Wall, Vector2(1.0f, 1.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(2.0f, 1.0f), Vector2(2.0f, 1.0f), eTileCollider::Wall, Vector2(1.0f, 1.0f));
		//	SceneManager::EditTile(eSceneType::Home, Vector2(2.0f, 0.0f), Vector2(2.0f, 0.0f), eTileCollider::Wall, Vector2(1.0f, 4.0f));
		//}
	}

	void HomeScene::Update()
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

	void HomeScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void HomeScene::Render()
	{
		Scene::Render();
	}

	void HomeScene::OnEnter()
	{
		//fade->FadeIn();
		CollisionManager::CollisionLayerCheck(eLayerType::Monster, eLayerType::PlayerProjectile);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::MonsterProjectile);
		CollisionManager::CollisionLayerCheck(eLayerType::PlayerProjectile, eLayerType::MonsterProjectile);
		renderer::player->GetOwner()->OnActive();
	}

	void HomeScene::OnExit()
	{

	}

}
