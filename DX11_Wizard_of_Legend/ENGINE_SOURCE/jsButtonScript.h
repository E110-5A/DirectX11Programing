#pragma once
#include "jsScript.h"

namespace js
{
	enum class eBtnFunc
	{

	};

	class Button : public Script
	{
	public:
		Button();
		virtual ~Button();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		void Action();
	private:
		bool mIsMouseOn;
	};
}