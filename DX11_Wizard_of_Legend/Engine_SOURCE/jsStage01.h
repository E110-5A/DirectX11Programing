#pragma once
#include "jsScene.h"

namespace js
{
	class Stage01Scene : public Scene
	{
	public:
		Stage01Scene();
		virtual ~Stage01Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}