#include "jsGridScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsApplication.h"
#include "jsConstantBuffer.h"
#include "jsRenderer.h"

extern js::Application application;

namespace js
{
	GridScript::GridScript()
		: Script()
		, mCamera(nullptr)
	{

	}

	GridScript::~GridScript()
	{

	}

	void GridScript::Initialize()
	{
		mCamera = renderer::cameras[0];
	}

	void GridScript::Update()
	{
	}

	void GridScript::FixedUpdate()
	{
		if (mCamera == nullptr)
			return;

		GameObject* gameObj = mCamera->GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		Vector3 cameraPos = tr->GetPosition();
		Vector4 position = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);

		float scale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = (float)(winRect.right - winRect.left);
		float height = (float)(winRect.bottom - winRect.top);
		Vector2 resolution(width, height);

		// Constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = position;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;

		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);
	}

	void GridScript::Render()
	{
	}

}
