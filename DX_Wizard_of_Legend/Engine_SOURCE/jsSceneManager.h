#pragma once
#include "jsScene.h"

namespace js
{
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Release();

		static Scene* GetActiveScene() { return mActiveScene; }
	private:
		static Scene* mActiveScene;
	};
}
