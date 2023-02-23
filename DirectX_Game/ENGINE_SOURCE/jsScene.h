#pragma once
#include "jsEntity.h"
#include "jsLayer.h"

namespace js
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* object, const enums::eLayerType type);
	private:
		std::vector<Layer> mLayers;
	};
}