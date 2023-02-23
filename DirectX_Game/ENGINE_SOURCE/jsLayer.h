#pragma once
#include "jsGameObject.h"

namespace js
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* object);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}