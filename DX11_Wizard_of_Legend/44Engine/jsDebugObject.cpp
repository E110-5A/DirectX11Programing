#include "jsDebugObject.h"

namespace js
{
	DebugObject::DebugObject()
	{
		GameObject::Initialize();
	}
	DebugObject::~DebugObject()
	{

	}

	void DebugObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->FixedUpdate();
		}
	}
}