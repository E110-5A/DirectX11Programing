#include "jsTransform.h"
#include "jsRenderer.h"
#include "jsCamera.h"

namespace js
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mForward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
		, mRotation(Vector3::Zero)
		, mPosition(Vector3::One)
		, mScale(Vector3::One)
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
	}
	void Transform::FixedUpdate()
	{
		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix position;
		position.Translation(mPosition);

		mWorldMatrix = scale * rotation * position;

		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
	}
	void Transform::Render()
	{
	}
	void Transform::SetConstantBuffer()
	{
		renderer::TransformCB transformCB = {};
		transformCB.world = mWorldMatrix;
		transformCB.view = Camera::GetViewMatrix();
		transformCB.projection = Camera::GetProjectionMatrix();

		ConstantBuffer* constantbuffer = renderer::constantBuffers[(UINT)eCBType::Transform];
		constantbuffer->Bind(&transformCB);
		constantbuffer->SetPipline(eShaderStage::VS);
	}
}