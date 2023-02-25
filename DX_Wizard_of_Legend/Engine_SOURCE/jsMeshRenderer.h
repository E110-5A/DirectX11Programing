#pragma once
#include "jsComponent.h"
#include "jsMesh.h"
#include "jsMaterial.h"

using namespace js::graphics;
namespace js
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetMaterial(Material* shader) { mMaterial = shader; }

	private:
		Mesh* mMesh;
		Material* mMaterial;
	};
}