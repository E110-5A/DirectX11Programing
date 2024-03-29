#include "jsCamera.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsApplication.h"
#include "jsRenderer.h"
#include "jsScene.h"
#include "jsSceneManager.h"
#include "jsMaterial.h"
#include "jsBaseRenderer.h"
#include "jsSceneManager.h"

extern js::Application application;

namespace js
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Orthographic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mScale(1.0f)
	{
		EnableLayerMasks();
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
		RegisterCameraInRenderer();
	}
	void Camera::Update()
	{

	}
	void Camera::FixedUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix();

		RegisterCameraInRenderer();
	}
	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		sortGameObjects();

		renderOpaque();
		renderCutout();
		renderTransparent();
	}

	void Camera::RegisterCameraInRenderer()
	{
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		renderer::cameras[(UINT)type].push_back(this);
	}

	void Camera::CreateViewMatrix()
	{
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector3 myPos = myTr->GetPosition();

		// Create Translate view matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-myPos);
		
		Vector3 up = myTr->Up();
		Vector3 right = myTr->Right();
		Vector3 foward = myTr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x; viewRotate._12 = up.x; viewRotate._13 = foward.x;
		viewRotate._21 = right.y; viewRotate._22 = up.y; viewRotate._23 = foward.y;
		viewRotate._31 = right.z; viewRotate._32 = up.z; viewRotate._33 = foward.z;

		mView *= viewRotate;
	}
	void Camera::CreateProjectionMatrix()
	{
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);

		float width = (winRect.right - winRect.left) * mScale;
		float height = (winRect.bottom - winRect.top) * mScale;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection 
				= Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}
		else
		{
			mProjection 
				= Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNear, mFar);
		}
	}

#pragma region Render Func
	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			// 카메라에 유효한 레이어인 경우
			if (mLayerMasks[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				GameObjects gameObjects = layer.GetGameObjects();
				if (gameObjects.size() == 0)
					continue;

				for (GameObject* obj : gameObjects)
				{
					pushGameObjectToRenderingModes(obj);
				}
			}
		}
	}
	void Camera::renderOpaque()
	{
		for (GameObject* obj : mOpaqueGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}
	void Camera::renderCutout()
	{
		for (GameObject* obj : mCutoutGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}
	void Camera::renderTransparent()
	{
		for (GameObject* obj : mTransparentGameObjects)
		{
			if (obj == nullptr)
				continue;

			obj->Render();
		}
	}
	void Camera::pushGameObjectToRenderingModes(GameObject* gameObj)
	{
		BaseRenderer* renderer = gameObj->GetComponent<BaseRenderer>();
		if (renderer == nullptr)
			return;
		// 렌더 모드에 따라서 각기 다른 queue에 등록함
		std::shared_ptr<Material> material = renderer->GetMaterial();		
		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case js::graphics::eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(gameObj);
			break;
		case js::graphics::eRenderingMode::CutOut:
			mCutoutGameObjects.push_back(gameObj);
			break;
		case js::graphics::eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(gameObj);
			break;
		default:
			break;
		}
	}
#pragma endregion
}
