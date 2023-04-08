#pragma once
#include "jsScene.h"
#include "jsLayer.h"
#include "jsGameObject.h"
#include "jsSceneManager.h"
#include "jsTransform.h"

namespace js::object
{
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
		gameObject->Death();
	}

	static void DontDestroyOnLoad(GameObject* gameObject)   //씬 이동시 이 오브젝트는 삭제하지 않는다
	{
		if (gameObject == nullptr)
			return;

		gameObject->DontDestroy();
	}
}