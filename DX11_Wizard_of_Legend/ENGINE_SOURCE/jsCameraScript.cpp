#include "jsCameraScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"

namespace js
{
	CameraScript::CameraScript()
		: mFollowTarget(nullptr)
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initialize()
	{
	}

	void CameraScript::Update()
	{
		CameraProcess();
	}
	void CameraScript::Render()
	{
	}
	void CameraScript::CameraProcess()
	{
		FollowTarget();
		CameraShake();
	}
	void CameraScript::FollowTarget()
	{
		if (nullptr == mFollowTarget
			|| GameObject::Active != mFollowTarget->GetState())
			return;

		Transform* cameraTr = GetOwner()->GetComponent<Transform>();
		Vector3 cameraPos = cameraTr->GetPosition();

		Transform* targetTr = mFollowTarget->GetComponent<Transform>();
		Vector3 targetPosition = targetTr->GetPosition();

		cameraPos = Vector3(targetPosition.x, targetPosition.y, cameraPos.z);
		cameraTr->SetPosition(cameraPos);
	}
	void CameraScript::CameraShake()
	{
		if (false == mShakeCamera)
			return;

		if (mCurrentShakeTime >= mShakeTime)
		{
			mCurrentShakeTime = 0.0f;
			mShakeCamera = false;
		}
		else
		{
			mCurrentShakeTime += Time::DeltaTime();
		}

		// Do
		float oscillationX = cos(mCurrentShakeTime * mOscillationPower);
		float oscillationY = sin(mCurrentShakeTime * mOscillationPower);

		Transform* CamTr = GetOwner()->GetComponent<Transform>();
		Vector3 position = CamTr->GetPosition();
		Vector3  oscillationPosition = Vector3(position.x + oscillationX / 25.0f, position.y + oscillationY / 25.0f, position.z);

		Transform* cameraTr = GetOwner()->GetComponent<Transform>();
		cameraTr->SetPosition(oscillationPosition);
	}
}