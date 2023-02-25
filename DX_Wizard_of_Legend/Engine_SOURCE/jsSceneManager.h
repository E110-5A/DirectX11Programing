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
	private:
		static Scene* mPlayScene;
	};
}
