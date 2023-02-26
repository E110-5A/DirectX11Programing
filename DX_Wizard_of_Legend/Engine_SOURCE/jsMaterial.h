#pragma once
#include "jsResource.h";
#include "jsRenderer.h"

#include "jsShader.h"
#include "jsTexture.h"

using namespace js::renderer;
namespace js::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Bind();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		std::shared_ptr<Shader> GetShader() { return mShader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		std::shared_ptr<Texture> GetTexture() { return mTexture; }

	private:
		std::shared_ptr<Shader>		mShader;
		std::shared_ptr<Texture>	mTexture;
		MaterialCB mCB;
	};
}
