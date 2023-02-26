#pragma once
#include "jsGameObject.h"

namespace js
{
	typedef const std::vector<GameObject*>& GameObjects;
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObject);
		const std::vector<GameObject*> GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
