#pragma once
#include "jsComponent.h"
#include "jsMesh.h"
#include "jsMaterial.h"
#include "jsBaseRenderer.h"

using namespace js::graphics;
namespace js
{
	class MeshRenderer : public BaseRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}