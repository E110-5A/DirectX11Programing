#pragma once
#include "jsScript.h"


namespace js
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void FollowTarget();

		void SetCamFollow(GameObject* target) { mFollowTarget = target; }

	private:
		GameObject* mFollowTarget;
	};
}
