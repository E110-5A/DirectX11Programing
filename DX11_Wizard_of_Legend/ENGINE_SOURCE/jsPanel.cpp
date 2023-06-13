#include "jsPanel.h"
#include "jsImage.h"

namespace js
{
	Panel::Panel(eUIType type)
		: UIBase(type)
	{
	}
	Panel::~Panel()
	{
	}

	void Panel::OnInit()
	{
	}

	void Panel::OnActive()
	{
	}

	void Panel::OnInActive()
	{
	}

	void Panel::OnTick()
	{
	}

	void Panel::OnRender(HDC hdc)
	{
		// 부모에서 렌더하는 기능 추가하기
	}

	void Panel::OnClear()
	{
	}

}