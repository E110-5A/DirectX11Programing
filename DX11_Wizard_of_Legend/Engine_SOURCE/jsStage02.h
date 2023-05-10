#pragma once
#include "jsScene.h"

namespace js
{
	class Stage02Scene : public Scene
	{
	public:
		Stage02Scene();
		virtual ~Stage02Scene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}