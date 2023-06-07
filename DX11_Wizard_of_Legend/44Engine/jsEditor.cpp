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
		// �浹ü�� ������ŭ ����� ��ü ����
		mDebugObjects.resize((UINT)eColliderType::End);

		// new Debug Object
		{
			// Rect
			mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
			MeshRenderer* renderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();
			renderer->SetMesh(Resources::Find<Mesh>(L"DebugRectMesh"));
			renderer->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));

			// Circle
			mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
			renderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();
			renderer->SetMesh(Resources::Find<Mesh>(L"DebugCircleMesh"));
			renderer->SetMaterial(Resources::Find<Material>(L"DebugMaterial"));
		}

		// Grid Object
		{
			EditorObject* gridObject = new EditorObject();
			MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>();
			gridMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			gridMr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridScript = gridObject->AddComponent<GridScript>();
			gridScript->SetCamera(mainCamera);

			mEditorObjects.push_back(gridObject);
		}
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

		// Debug Obj : Pos, Rotate, Scale Renewal
		Transform* debugTr = debugObj->GetComponent<Transform>();
		debugTr->SetPosition(mesh.position);
		debugTr->SetRotation(mesh.rotatation);
		if (mesh.type == eColliderType::Rect)
			debugTr->SetScale(mesh.scale);
		if (mesh.type == eColliderType::Circle)
			debugTr->SetScale(Vector3(mesh.radius));
		debugTr->FixedUpdate();

		BaseRenderer* debugRenderer = debugObj->GetComponent<BaseRenderer>(); // <- �ϴ��� ����
		// Camera Update Renewal
		Camera* camera = renderer::mainCamera;
		Matrix viewM = renderer::mainCamera->GetViewMatrix();
		Camera::SetGpuViewMatrix(viewM);
		Camera::SetGpuProjectionMatrix(renderer::mainCamera->GetProjectionMatrix());
		
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