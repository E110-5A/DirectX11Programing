#pragma once
#include "jsEntity.h"
#include "jsComponent.h"
#include "jsScript.h"

namespace js
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddComponent(Component* comp);

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
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

			return component;
		}

		template <typename T>
		T* GetComponent()
		{
			T* retComponent;
			for (auto component : mComponents)
			{
				retComponent = dynamic_cast<T*>(component);

				if (retComponent != nullptr)
					return retComponent;
			}

			return nullptr;
		}

		bool IsDead()
		{
			if (eState::Dead == mState)
				return true;

			return false;
		}

		void Pause() { mState = eState::Paused; }
		void Death() { mState = eState::Dead; }
		eState GetState() { return mState; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Component*> mScripts;
	};
}
