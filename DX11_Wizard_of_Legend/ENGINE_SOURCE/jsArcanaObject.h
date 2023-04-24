#pragma once
#include "jsGameObject.h"

namespace js
{
	class Arcana : public GameObject
	{
	public:
		Arcana();
		virtual ~Arcana();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
	};
}