#include "jsLayer.h"


namespace js
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
				continue;

			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initalize()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
				continue;

			obj->Initalize();
		}
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
				continue;
			if (GameObject::eState::Active != obj->GetState())
				continue;

			obj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
				continue;
			if (GameObject::eState::Active != obj->GetState())
				continue;

			obj->FixedUpdate();
		}
	}

	void Layer::Render()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
				continue;
			if (GameObject::eState::Active != obj->GetState())
				continue;

			obj->Render();
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
			return;

		mGameObjects.push_back(gameObject);
	}
}