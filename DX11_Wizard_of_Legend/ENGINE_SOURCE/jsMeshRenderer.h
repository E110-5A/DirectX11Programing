#pragma once
#include "jsBaseRenderer.h"
#include "jsMesh.h"
#include "jsMaterial.h"

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