#pragma once
#include "jsComponent.h"

using namespace js::math;

namespace js
{
	class Camera : public Component
	{
	public:
		enum eProjectionType
		{
			Perspective,
			Orthographic,
		};
		__forceinline static Matrix& GetViewMatrix() { return mView; }
		__forceinline static Matrix& GetProjectionMatrix() { return mProjection; }

		Camera();
		virtual ~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void CreateViewMatrix();
		void CreateProjectionMatrix();

	private:
		static Matrix mView;
		static Matrix mProjection;

		eProjectionType mType;
		float mScale;
		float mAspectRatio;
		float mNear;
		float mFar;
	};
}