#include "jsUIGameObject.h"
#include "jsAnimator.h"
#include "jsResources.h"

namespace js
{
	UIGameObject::UIGameObject()
	{
	}
	UIGameObject::~UIGameObject()
	{
	}
	void UIGameObject::Initialize()
	{
	}
	void UIGameObject::Tick()
	{
		GameObject::Tick();
	}
	void UIGameObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}