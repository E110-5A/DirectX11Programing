#include "jsGridScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsApplication.h"
#include "jsConstantBuffer.h"
#include "jsRenderer.h"
#include "jsSceneManager.h"

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
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		mCamera = renderer::cameras[(UINT)type][0];
	}

	void GridScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* camObj = mCamera->GetOwner();
		Transform* camTr = camObj->GetComponent<Transform>();
		
		Vector3 camTrPos = camTr->GetPosition();
		Vector4 cameraPosition = Vector4(camTrPos.x, camTrPos.y, camTrPos.z, 1.0f);

		float scale = mCamera->GetScale();

		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = float(winRect.right - winRect.left);
		float height = float(winRect.bottom - winRect.top);
		Vector2 resolution(width, height);

		// Constant buffer
		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];
		renderer::GridCB data;
		data.cameraPosition = cameraPosition;
		data.cameraScale = Vector2(scale, scale);
		data.resolution = resolution;

		cb->Bind(&data);
		cb->SetPipline(eShaderStage::VS);
		cb->SetPipline(eShaderStage::PS);
 	}

	void GridScript::FixedUpdate()
	{
	}

	void GridScript::Render()
	{
	}

}
