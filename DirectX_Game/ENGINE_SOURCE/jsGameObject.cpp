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
		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->Initialize();
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
		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->Initialize();
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
		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->Initialize();
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
		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;
			script->Initialize();
		}
	}
	void GameObject::AddComponent(Component* component)
	{
		eComponentType order = component->GetOrder();
	
		if (eComponentType::Script != order)
		{
			mComponents[(UINT)order] = component;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScripts.push_back(component);
			component->SetOwner(this);
		}
		
	}
}