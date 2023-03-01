#pragma once
#include "jsEntity.h"
#include "jsLayer.h"
#include "jsGameObject.h"

namespace js
{
	using namespace enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObj, const eLayerType type);
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }


	private:
		std::vector<Layer> mLayers;
	};
}
