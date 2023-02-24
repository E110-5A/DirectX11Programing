#pragma once
#include "jsResource.h"
#include "jsShader.h"
#include "jsRenderer.h"

using namespace js::renderer;

namespace js::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		virtual HRESULT Load(const std::wstring& strPath) override;

		void SetData(eGPUParam param, void* data);
		void Bind();

		void SetShader(Shader* shader) { mShader = shader; }
		Shader* GetShader() { return mShader; }

	private:
		Shader* mShader;
		MaterialCB mCB;
	};
}