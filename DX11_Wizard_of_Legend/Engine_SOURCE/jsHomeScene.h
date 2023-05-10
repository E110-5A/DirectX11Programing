#pragma once
#include "jsScene.h"

namespace js
{
	class HomeScene : public Scene
	{
	public:
		HomeScene();
		virtual ~HomeScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}