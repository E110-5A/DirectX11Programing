#pragma once
#include "jsScene.h"

namespace js
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetScene(eSceneType type) { return mScenes[(UINT)type]; };
		static void MoveDontDestoryObjects(eSceneType type);

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}
