#include "jsScene.h"

namespace js
{
	Scene::Scene()
	{
		mLayers.resize((UINT)enums::eLayerType::End);
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
	void Scene::AddGameObject(GameObject* object, const enums::eLayerType type)
	{
		mLayers[(UINT)type].AddGameObject(object);
	}
}