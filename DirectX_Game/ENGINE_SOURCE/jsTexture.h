#pragma once
#include "jsResource.h"
#include "DirectXTex\Include\DirectXTex.h"
#include "jsGraphicDevice_DX11.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

using namespace js::enums;

namespace js::graphics
{
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& name) override;
		
		void BindShader(eShaderStage stage, UINT slot);

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}