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
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetParent(parent);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);

		Transform* tr = obj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);

		return obj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Transform* parent)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);

		Transform* tr = obj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetParent(parent);

		return obj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(gameObj);

		Transform* tr = gameObj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);
		tr->SetParent(parent);

		return gameObj;
	}


	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation, Vector3 scale)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);

		Transform* tr = obj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);
		tr->SetScale(scale);

		return obj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation, Vector3 scale, Transform* parent)
	{
		T* obj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		layer.AddGameObject(obj);

		Transform* tr = obj->GameObject::GetComponent<Transform>();
		tr->SetPosition(position);
		tr->SetRotation(rotation);
		tr->SetScale(scale);
		tr->SetParent(parent);

		return obj;
	}

	void Destroy(GameObject* gameObject)
	{
		gameObject->Death();
	}
}