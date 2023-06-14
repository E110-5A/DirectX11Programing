#pragma once
#include "jsScene.h"
#include "jsPlayer.h"

namespace js
{
	class GameManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();

#pragma region GameObject
		static void SetPlayer(Player* player) { mPlayer = player; }
		static Player* GetPlayer() { return mPlayer; }

		static void SetPlayer(Player* player) { mPlayer = player; }
		static Player* SetPlayer() { return mPlayer; }
#pragma endregion

	private:
		static Player* mPlayer;
	};
}
