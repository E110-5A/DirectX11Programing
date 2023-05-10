#pragma once
#include "jsScene.h"

namespace js
{
	class Stage01BossScene : public Scene
	{
	public:
		Stage01BossScene();
		virtual ~Stage01BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}