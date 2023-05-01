#pragma once
#include "jsComponent.h"
#include "jsMesh.h"
#include "jsMaterial.h"

namespace js
{
	class BaseRenderer : public Component
	{
	public:
		BaseRenderer(eComponentType type);
		virtual ~BaseRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		std::shared_ptr<Mesh> SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; return mesh; }
		std::shared_ptr<Material> SetMaterial(std::shared_ptr <Material> material) { mMaterial = material; return material; }
		std::shared_ptr<Mesh> GetMesh() { return mMesh; }
		std::shared_ptr<Material> GetMaterial() { return mMaterial; }

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
	};
}
