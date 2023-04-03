#include "jsEntity.h"

namespace js
{
	Entity::Entity()
		: mID((UINT32)reinterpret_cast<UINT32>(this))
	{
	}
	Entity::Entity(const Entity& other)
		: mID((UINT32)reinterpret_cast<UINT32>(this))
		, mName(other.mName)
	{
	}
	Entity::~Entity()
	{
	}
}