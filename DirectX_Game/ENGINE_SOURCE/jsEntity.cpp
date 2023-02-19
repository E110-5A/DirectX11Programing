#include "jsEntity.h"

namespace js
{
	Entity::Entity()
		: mID(reinterpret_cast<UINT32>(this))
		, mName(L"")
	{}
	Entity::Entity(const Entity& other)
		: mID(reinterpret_cast<UINT32>(this))
		, mName(other.mName)
	{}

	Entity::~Entity()
	{}
}