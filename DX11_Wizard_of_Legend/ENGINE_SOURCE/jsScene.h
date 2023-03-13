#pragma once
#include "jsEntity.h"
#include "jsLayer.h"
#include "jsGameObject.h"

namespace js
{
	using namespace js::enums;
	class Scene : public Entity
	{
	public:
		Scene(eSceneType type);
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		eSceneType GetSceneType() { return mType; }
		void AddGameObject(GameObject* gameObj, const eLayerType type);
		Layer& GetLayer(eLayerType type) { return mLayers[(UINT)type]; }
		const std::vector<GameObject*>& GetGameObjects(const eLayerType layer);

		std::vector<GameObject*> GetDontDestroyGameObjects();

		void ObjectsActive();
		void ObjectsPause();

	private:
		std::vector<Layer> mLayers;
		eSceneType mType;
	};
}
