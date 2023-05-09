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
		FollowTarget();
	}
	void CameraScript::Render()
	{
	}
	void CameraScript::FollowTarget()
	{
		if (nullptr == mFollowTarget)
			return;
		if (GameObject::Active != mFollowTarget->GetState())
			return;

		Transform* cameraTr = GetOwner()->GetComponent<Transform>();
		Vector3 cameraPos = cameraTr->GetPosition();

		Transform* targetTr = mFollowTarget->GetComponent<Transform>();
		Vector3 targetPosition = targetTr->GetPosition();

		cameraPos = Vector3(targetPosition.x, targetPosition.y, cameraPos.z);
		cameraTr->SetPosition(cameraPos);
	}
}