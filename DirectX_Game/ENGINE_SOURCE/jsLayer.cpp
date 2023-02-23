#include "jsLayer.h"

namespace js
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
	}
	void Layer::Initialize()
	{
		for (GameObject* object : mGameObjects)
		{
			if (nullptr == object)
				continue;
			object->Initialize();
		}
	}
	void Layer::Update()
	{
		for (GameObject* object : mGameObjects)
		{
			if (nullptr == object)
				continue;
			object->Update();
		}
	}
	void Layer::FixedUpdate()
	{
		for (GameObject* object : mGameObjects)
		{
			if (nullptr == object)
				continue;
			object->FixedUpdate();
		}
	}
	void Layer::Render()
	{
		for (GameObject* object : mGameObjects)
		{
			if (nullptr == object)
				continue;
			object->Render();
		}
	}
	void Layer::AddGameObject(GameObject* object)
	{
		if (nullptr == object)
			return;
		mGameObjects.push_back(object);
	}
}