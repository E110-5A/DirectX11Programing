#pragma once
#include "jsScript.h"
namespace js
{
	class MouseScript : public Script
	{
	public:
		MouseScript();
		virtual ~MouseScript();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}