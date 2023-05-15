#pragma once
#include "jsSceneManager.h"
#include "jsScene.h"
#include "jsLayer.h"
#include "jsTime.h"

#include "jsGameObject.h"
#include "jsSpriteRenderer.h"


#include "GameObjectComponents.h"


namespace js::object
{
	template <typename T>
	static T* InstantiateGameObject(enums::eLayerType type, Scene* scene)
	{
		T* obj = new T();										// 이떄 Transform 추가됨
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);
		GameObject* gameObj = dynamic_cast<GameObject*>(obj);
		if (nullptr != gameObj)
		{
			gameObj->SetLayerType(type);
			gameObj->Initialize();
		}
		SpriteRenderer* sr = gameObj->AddComponent<SpriteRenderer>();
		sr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		sr->SetMaterial(Resources::Find<Material>(L"ObjectMaterial"));
		return obj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);
		GameObject* gameObj = dynamic_cast<GameObject*>(obj);
		if (nullptr != gameObj)
		{
			gameObj->SetLayerType(type);
			gameObj->Initialize();
		}

		return obj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Scene* scene)
	{
		T* obj = new T();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);
		GameObject* gameObj = dynamic_cast<GameObject*>(obj);
		if (nullptr != gameObj)
		{
			gameObj->SetLayerType(type);
			gameObj->Initialize();
		}
		return obj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Transform* parent)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);
		GameObject* gameObj = dynamic_cast<GameObject*>(obj);
		if (nullptr != gameObj)
		{
			gameObj->SetLayerType(type);
			gameObj->Initialize();
		}
		Transform* tr = obj->GameObject::GetComponent<Transform>();
		tr->SetParent(parent);

		return obj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);
		GameObject* gameObj = dynamic_cast<GameObject*>(obj);
		if (nullptr != gameObj)
		{
			gameObj->SetLayerType(type);
			gameObj->Initialize();
		}
		Transform* tr = obj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);

		return obj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation, Transform* parent)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);
		GameObject* gameObj = dynamic_cast<GameObject*>(obj);
		if (nullptr != gameObj)
		{
			gameObj->SetLayerType(type);
			gameObj->Initialize();
		}
		Transform* tr = obj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);
		tr->SetParent(parent);

		return obj;
	}

	static void Destroy(GameObject* gameObject)
	{
		gameObject->OnDeath();
	}

	static void DontDestroyOnLoad(GameObject* gameObject)   //씬 이동시 이 오브젝트는 삭제하지 않는다
	{
		if (gameObject == nullptr)
			return;

		gameObject->DontDestroy();
	}
}