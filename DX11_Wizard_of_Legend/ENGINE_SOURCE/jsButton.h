#pragma once
#include "jsUIBase.h"

namespace js
{
	class Button : public UIBase
	{
	public:
		
		Button(eUIType type);
		~Button();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		virtual void Click();

		void SetFunc(eBtnType type) { mFunc = type; }

	private:
		Event mOnClick;
		bool mIsMouseOn;
		eBtnType mFunc;
	};
}