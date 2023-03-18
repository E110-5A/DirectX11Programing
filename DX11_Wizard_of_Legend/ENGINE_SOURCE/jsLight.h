#pragma once
#include "jsComponent.h"
#include "jsGraphics.h"

namespace js
{
	class Light : public Component
	{
	public:
		Light();
		virtual ~Light();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		graphics::LightAttribute GetLightAttribute() { return mAttribute; }

		void SetDiffuse(Vector4 diffuse) { mAttribute.diffuse = diffuse; }
		void SetAmbient(Vector4 ambient) { mAttribute.ambient = ambient; }
		void SetLightType(eLightType type) { mAttribute.lightType = type; }
		void SetRadius(float radius) { mAttribute.radius = radius; }
		void SetAngle(float angle) { mAttribute.angle = angle; }

		Vector4 GetDiffuse() { return mAttribute.diffuse; }
		eLightType GetLightType() { return mAttribute.lightType; }
		float GetRadius() { return mAttribute.radius; }
		float GetAngle() { return mAttribute.angle; }

	private:
		graphics::LightAttribute mAttribute;
	};
}