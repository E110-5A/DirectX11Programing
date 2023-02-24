#include "jsCamera.h"
#include "jsApplication.h"

#include "jsTransform.h"
#include "jsGameObject.h"

extern js::Application application;

namespace js
{
	Matrix Camera::mView = Matrix::Identity;
	Matrix Camera::mProjection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Perspective)
		, mScale(1.0f)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
	}
	void Camera::Update()
	{
	}
	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();
	}
	void Camera::Render()
	{
	}
	void Camera::CreateViewMatrix()
	{
		Transform* transform = GetOwner()->GetComponent<Transform>();
		Vector3 position = transform->GetPosition();

		mView = Matrix::Identity;
		mView = Matrix::CreateTranslation(-position);

		Vector3 right = transform->Right();
		Vector3 up = transform->Up();
		Vector3 forward = transform->Forward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = forward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = forward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = forward.z;

		mView *= viewRotate;
	}
	void Camera::CreateProjectionMatrix()
	{
		RECT windowRect;
		GetClientRect(application.GetHwnd(), &windowRect);

		float width = windowRect.right - windowRect.left;
		float height = windowRect.bottom - windowRect.top;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH
			(
				XM_2PI / 6.0f
				, mAspectRatio
				, mNear
				, mFar
			);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
	}
}