#pragma once
#include "jsResource.h"
#include "jsShader.h"
#include "jsTexture.h"
#include "jsRenderer.h"

using namespace js::renderer;
namespace js::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		virtual ~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGpuParam param, void* data);
		void Bind();
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		std::shared_ptr<Shader> GetShader() { return mShader; }
		void SetTexture(eTextureSlot slot, std::shared_ptr<Texture> texture) { mTexture[(UINT)slot] = texture; }
		std::shared_ptr<Texture> GetTexture(eTextureSlot slot) { return mTexture[(UINT)slot]; }

		eRenderingMode GetRenderingMode() { return mMode; }
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture[(UINT)eTextureSlot::End];
		MaterialCB mCB;
		eRenderingMode mMode;
	};
}

