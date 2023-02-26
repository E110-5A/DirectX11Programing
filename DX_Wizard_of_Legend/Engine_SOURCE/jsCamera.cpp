#include "jsCamera.h"
#include "jsApplication.h"
#include "jsRenderer.h"
#include "jsSceneManager.h"

#include "jsScene.h"
#include "jsGameObject.h"
#include "jsMaterial.h"

#include "jsBaseRenderer.h"
#include "jsTransform.h"

extern js::Application application;


namespace js
{
	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Perspective)
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

	void Camera::Initalize()
	{
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

	void Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 foward = tr->Foward();

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

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		mAspectRatio = width / height;

		if (mType == eProjectionType::Perspective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}
		else
		{
			mProjection = Matrix::CreateOrthographicLH(width / 100.0f, height / 100.0f, mNear, mFar);
		}
	}
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}
	void Camera::TurnLayerMask(eLayerType layer, bool enable)
	{
		mLayerMasks.set((UINT)layer, enable);
	}
	void Camera::sortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutoutGameObjects.clear();
		mTransparentGameObjects.clear();

		Scene* scene = SceneManager::GetActiveScene();
		for (size_t type = 0; type < (UINT)eLayerType::End; ++type)
		{
			if (true == mLayerMasks[type])
			{
				Layer& layer = scene->GetLayer((eLayerType)type);
				GameObjects gameObjects = layer.GetGameObjects();
				if (0 == gameObjects.size())
					continue;

				for (GameObject* object : gameObjects)
				{
					pushGameObjectToRenderingModes(object);
				}
			}
		}
	}
	void Camera::renderOpaque()
	{
		for (GameObject* object : mOpaqueGameObjects)
		{
			if (nullptr == object)
				continue;

			object->Render();
		}
	}
	void Camera::renderCutout()
	{
		for (GameObject* object : mCutoutGameObjects)
		{
			if (nullptr == object)
				continue;

			object->Render();
		}
	}
	void Camera::renderTransparent()
	{
		for (GameObject* object : mTransparentGameObjects)
		{
			if (nullptr == object)
				continue;

			object->Render();
		}
	}
	void Camera::pushGameObjectToRenderingModes(GameObject* object)
	{
		BaseRenderer* renderer = object->GetComponent<BaseRenderer>();
		if (nullptr == renderer)
			return;

		std::shared_ptr<Material> material = renderer->GetMaterial();
		eRenderingMode mode = material->GetRenderingMode();

		switch (mode)
		{
		case eRenderingMode::Opaque:
			mOpaqueGameObjects.push_back(object);
			break;
		case eRenderingMode::Cutout:
			mCutoutGameObjects.push_back(object);
			break;
		case eRenderingMode::Transparent:
			mTransparentGameObjects.push_back(object);
			break;
		default:
			break;
		}
	}
}