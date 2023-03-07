#pragma once
#include "jsGameObject.h"

namespace js
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;

	private:
	};
}