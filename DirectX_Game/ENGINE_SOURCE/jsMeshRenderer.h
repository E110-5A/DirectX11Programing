#pragma once
#include "jsComponent.h"
#include "jsMesh.h"
#include "jsShader.h"

namespace js
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetShader(Shader* shader) { mShader = shader; }

	private:
		Mesh* mMesh;
		Shader* mShader;
	};
}