#pragma once
#include "jsGameObject.h"

namespace js
{
	class Image;
	class Animator;
	class UIGameObject : public GameObject
	{
	public:
		UIGameObject();
		~UIGameObject();

		void Initialize();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
	private:
		Animator* mAnimator;
		Image* mImage;

	};
}