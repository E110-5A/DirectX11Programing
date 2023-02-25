#pragma once
#include "jsComponent.h"
#include "jsMesh.h"
#include "jsMaterial.h"

using namespace js::graphics;
namespace js
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr <Material> shader) { mMaterial = shader; }

	private:
		std::shared_ptr <Mesh> mMesh;
		std::shared_ptr <Material> mMaterial;
	};
}