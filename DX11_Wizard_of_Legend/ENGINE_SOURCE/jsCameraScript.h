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


		void CameraProcess();
		void FollowTarget();

		void SetCamFollow(GameObject* target) { mFollowTarget = target; }

	public:
		void CameraShake();
		// 흔들리는정도, 흔들림 유지시간
		void SetOscillation(float oscillationPower, float time)
		{
			mShakeCamera = true;
			mOscillationPower = oscillationPower;
			mShakeTime = time;
		}

	private:
		GameObject* mFollowTarget;

	private:
		bool mShakeCamera;
		float mOscillationPower;
		float mShakeTime;
		float mCurrentShakeTime;
	};
}
