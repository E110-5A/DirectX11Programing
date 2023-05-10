#pragma once
#include "jsScene.h"

namespace js
{
	class Stage02BossScene : public Scene
	{
	public:
		Stage02BossScene();
		virtual ~Stage02BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}