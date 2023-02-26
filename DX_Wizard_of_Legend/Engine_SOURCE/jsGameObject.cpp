#include "jsGameObject.h"
#include "jsTransform.h"

namespace js
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		mComponents.resize((UINT)eComponentType::End);
		AddComponent(new Transform());
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (nullptr == comp)
				continue;

			delete comp;
			comp = nullptr;
		}

		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;

			delete script;
			script = nullptr;
		}
	}

	void GameObject::Initalize()
	{
		for (Component* comp : mComponents)
		{
			if (nullptr == comp)
				continue;

			comp->Initalize();
		}

		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;

			script->Initalize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (nullptr == comp)
				continue;

			comp->Update();
		}

		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;

			script->Update();
		}
	}

	void GameObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (nullptr == comp)
				continue;

			comp->FixedUpdate();
		}

		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;

			script->FixedUpdate();
		}
	}

	void GameObject::Render()
	{
		for (Component* comp : mComponents)
		{
			if (nullptr == comp)
				continue;

			comp->Render();
		}

		for (Component* script : mScripts)
		{
			if (nullptr == script)
				continue;

			script->Render();
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
		eComponentType order = comp->GetOrder();

		if (eComponentType::Script != order)
		{
			mComponents[(UINT)order] = comp;
			mComponents[(UINT)order]->SetOwner(this);
		}
		else
		{
			mScripts.push_back(comp);
			comp->SetOwner(this);
		}
	}
}
