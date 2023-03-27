#pragma once
#include "jsScript.h"

namespace js
{
	class Random : public Script
	{
	public:
		Random();
		virtual ~Random();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}