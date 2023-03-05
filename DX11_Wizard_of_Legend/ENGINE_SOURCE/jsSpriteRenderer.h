#pragma once
#include "jsBaseRenderer.h"
#include "jsMesh.h"
#include "jsMaterial.h"

using namespace js::graphics;
namespace js
{
	class SpriteRenderer : public BaseRenderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}
