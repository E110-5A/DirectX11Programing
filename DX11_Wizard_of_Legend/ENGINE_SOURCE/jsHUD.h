#pragma once
#include "jsUIBase.h"

namespace js
{
	class HUD : public UIBase
	{
	public:
		HUD(eUIType type);
		virtual ~HUD();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;
			
	};
}