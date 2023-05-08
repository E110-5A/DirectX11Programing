#include "jsEditor.h"
#include "jsResources.h"
#include "jsMesh.h"
#include "jsMaterial.h"
#include "jsObject.h"

#include "jsTransform.h"
#include "jsMeshRenderer.h"
#include "jsGridScript.h"

namespace js
{	
	void Editor::Initialize()
	{
		// 카메라 설정?



		// 충돌체의 종류 갯수만큼 디버그 객체 생성
		mDebugObjects.resize((UINT)eColliderType::End);

		// DebugRect Object
		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();		
		MeshRenderer* renderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();
		renderer->SetMesh(Resources::Find<Mesh>(L"DebugRectMesh"));
		renderer->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));

		// DebugCircle Object
		mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
		renderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();
		renderer->SetMesh(Resources::Find<Mesh>(L"DebugCircleMesh"));
		renderer->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));

		// Grid Object
		EditorObject* gridObject = new EditorObject();
		MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
		gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		GridScript* gridScript = gridObject->AddComponent<GridScript>();
		gridScript->SetCamera(mainCamera);

		mEditorObjects.push_back(gridObject);

	}
	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void Editor::FixedUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->FixedUpdate();
		}
	}
	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (DebugMesh& mesh : renderer::debugMeshes)
		{
			DebugRender(mesh);
		}
		renderer::debugMeshes.clear();
	}
	void Editor::DebugRender(graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// Tr
		Transform* debugTr = debugObj->GetComponent<Transform>();
		debugTr->SetPosition(mesh.position);
		debugTr->SetRotation(mesh.rotatation);
		// Tr->Collider
		if (mesh.type == eColliderType::Rect)
			debugTr->SetScale(mesh.scale);
		if (mesh.type == eColliderType::Circle)
			debugTr->SetScale(Vector3(mesh.radius));

		// Camera Update
		BaseRenderer* debugRenderer = debugObj->GetComponent<BaseRenderer>();
		Camera* camera = renderer::mainCamera;
		Matrix viewM = renderer::mainCamera->GetViewMatrix();
		Camera::SetGpuViewMatrix(viewM);
		Camera::SetGpuProjectionMatrix(renderer::mainCamera->GetProjectionMatrix());

		debugTr->FixedUpdate();
		
		// Final Render
		debugObj->Render();
	}
	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}
	void Editor::Release()
	{
		for (auto obj : mWidgets)
		{
			delete obj;
			obj = nullptr;
		}
		for (auto obj : mEditorObjects)
		{
			delete obj;
			obj = nullptr;
		}

		delete mDebugObjects[(UINT)eColliderType::Rect];
		delete mDebugObjects[(UINT)eColliderType::Circle];
	}
}