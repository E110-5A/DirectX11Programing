#include "jsScene.h"


namespace js
{
	Scene::Scene(eSceneType type)
		: mType(type)
		, mFadeObject(nullptr)
	{
		mLayers.resize((UINT)eLayerType::End);
	}
	Scene::~Scene()
	{

	}
	void Scene::Initialize()
	{
		for (Layer& layer : mLayers)
		{
			layer.Initialize();
		}
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::FixedUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.FixedUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::Destroy()
	{
		for (Layer& layer : mLayers)
		{
			layer.Destroy();
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(GameObject* gameObj, const eLayerType type)
	{
		mLayers[(UINT)type].AddGameObject(gameObj);
		gameObj->SetLayerType(type);
	}

	const std::vector<GameObject*>& Scene::GetGameObjects(const eLayerType layer)
	{
		return mLayers[(UINT)layer].GetGameObjects();
	}
	
	std::vector<GameObject*> Scene::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> gameObjects;
		for (Layer& layer : mLayers)
		{
			std::vector<GameObject*> dontGameObjs
				= layer.GetDontDestroyGameObjects();

			gameObjects.insert(gameObjects.end()
			, dontGameObjs.begin()
			, dontGameObjs.end());
		}

		return gameObjects;
	}
	void Scene::ObjectsActive()
	{
		for (Layer& layer : mLayers)
		{
			layer.ObjectsActive();
		}
	}
	void Scene::ObjectsPause()
	{
		for (Layer& layer : mLayers)
		{
			layer.ObjectsPause();
		}
	}
}
