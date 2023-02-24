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

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddComponent(Component* component);

		template <typename T>
		T* GetComponent()
		{
			T* retComponent;
			for (auto component : mComponents)
			{
				retComponent = dynamic_cast<T*>(component);

				if (nullptr != retComponent)
					return retComponent;
			}
			return nullptr;
		}

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::vector<Component*> mScripts;
	};
}