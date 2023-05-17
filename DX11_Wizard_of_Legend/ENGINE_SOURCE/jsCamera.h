#pragma once
#include "jsComponent.h"

namespace js
{
	using namespace math;
	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective,
			Orthographic,
		};

		__forceinline static Matrix& GetGpuViewMatrix() { return View; }
		__forceinline static Matrix& GetGpuProjectionMatrix() { return Projection; }
		__forceinline static void SetGpuViewMatrix(Matrix view) { View = view; }
		__forceinline static void SetGpuProjectionMatrix(Matrix projection) { Projection = projection; }

		Camera();
		virtual ~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
#pragma region CameraTick Func
		void RegisterCameraInRenderer();
		void CreateViewMatrix();
		void CreateProjectionMatrix();
#pragma endregion
	public:
#pragma region LayerMaskSet Func
		void TurnLayerMask(eLayerType layer, bool enable = true) { mLayerMasks.set((UINT)layer, enable); }
		void EnableLayerMasks() { mLayerMasks.set(); }
		void DisableLayerMasks() { mLayerMasks.reset(); }
#pragma endregion
	public:
#pragma region TransformMatrix Func
		void SetProjectionType(eProjectionType type) { mType = type; }
		float GetScale() { return mScale; }
		Matrix& GetViewMatrix() { return mView; }
		Matrix& GetProjectionMatrix() { return mProjection; }
#pragma endregion
	private:
#pragma region RenderObjects Func
		void sortGameObjects();
		void renderOpaque();
		void renderCutout();
		void renderTransparent();
		void pushGameObjectToRenderingModes(GameObject* gameObj);
#pragma endregion
		void CameraOscillation();
		void TurnOnCameraShake();

	private:
#pragma region RenderTransform Member
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;

		float mNear;
		float mFar;
		float mScale;
#pragma endregion
#pragma region RenderObjects Member
		std::bitset<(UINT)eLayerType::End> mLayerMasks;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutoutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;
#pragma endregion

		// 카메라 진동 조건용 bool 변수 하나
		// 진도와 유지시간용 float 변수 여러개
		// Transform 정보
		// position 기록용 vector3 변수 하나
	};
}
