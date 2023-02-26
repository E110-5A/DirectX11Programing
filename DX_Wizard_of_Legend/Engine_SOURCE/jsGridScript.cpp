#include "jsGridScript.h"
#include "jsApplication.h"
#include "jsConstantBuffer.h"
#include "jsRenderer.h"

#include "jsGameObject.h"
#include "jsTransform.h"

extern js::Application application;

namespace js
{
	GridScript::GridScript()
	{
	}
	GridScript::~GridScript()
	{
	}
	void GridScript::Initalize()
	{
		mCamera = renderer::cameras[0];
	}
	void GridScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* camObj = mCamera->GetOwner();
		Transform* camTr = camObj->GetComponent<Transform>();

		Vector3 camPosition = camTr->GetPosition();
		Vector4 cbInPosition = Vector4(camPosition.x, camPosition.y, camPosition.z, 1.0f);

		float camScale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 cbInResolution(width, height);

		// Constant buffer
		ConstantBuffer* gridCB = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = cbInPosition;
		data.cameraScale = Vector2(camScale, camScale);
		data.resolution = cbInResolution;

		gridCB->Bind(&data);
		gridCB->SetPipline(eShaderStage::VS);
		gridCB->SetPipline(eShaderStage::PS);
	}
	void GridScript::FixedUpdate()
	{
	}
	void GridScript::Render()
	{
	}
}