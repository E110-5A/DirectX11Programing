#include "jsComponent.h"

namespace js
{
	Component::Component(enums::eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}
	Component::~Component()
	{
	}
}