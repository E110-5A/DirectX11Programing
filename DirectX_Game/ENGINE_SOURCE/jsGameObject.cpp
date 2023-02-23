#include "jsGameObject.h"

namespace js
{
	GameObject::GameObject()
	{
		mComponents.resize((UINT)enums::eComponentType::End);
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::Initialize()
	{
		for (Component* component : mComponents)
		{
			if (nullptr == component)
				continue;
			component->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* component : mComponents)
		{
			if (nullptr == component)
				continue;
			component->Update();
		}
	}
	void GameObject::FixedUpdate()
	{
		for (Component* component : mComponents)
		{
			if (nullptr == component)
				continue;
			component->FixedUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* component : mComponents)
		{
			if (nullptr == component)
				continue;
			component->Render();
		}
	}
	void GameObject::AddComponent(Component* component)
	{
		int order = component->GetOrder();
		mComponents[order] = component;
		mComponents[order]->SetOwner(this);
	}
}