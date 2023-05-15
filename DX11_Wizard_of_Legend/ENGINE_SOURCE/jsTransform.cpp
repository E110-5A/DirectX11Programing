#include "jsTransform.h"
#include "jsRenderer.h"
#include "jsCamera.h"
#include "jsTime.h"

namespace js
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mFoward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
		, mScale(Vector3::One)
		, mRotation(Vector3::Zero)
		, mPosition(Vector3::One)
		, mParent(nullptr)
	{
		
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
		ShakeCamera();
	}

	void Transform::FixedUpdate()
	{
		// 월드 행렬 생성

		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix position;

		if (false == mShakeCamera)
		{
			position.Translation(mPosition);
		}
		else
		{
			position.Translation(mOscillationPosition);
		}

		mWorld = scale * rotation * position;

		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		
		// 부모 자식 관계인 경우
		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCb = {};
		trCb.world = mWorld;
		trCb.view = Camera::GetGpuViewMatrix();
		trCb.projection = Camera::GetGpuProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}
	void Transform::ShakeCamera()
	{
		if (false == mShakeCamera)
			return;
		if (mCurrentShakeTime >= mShakeTime)
		{
			mCurrentShakeTime = 0.0f;
			mShakeCamera = false;
		}
		// Do
		float oscillation = cos(Time::DeltaTime()) * mOscillationPower;

		mOscillationPosition = Vector3(mPosition.x + oscillation, mPosition.y + oscillation, mPosition.z);
	}
}
