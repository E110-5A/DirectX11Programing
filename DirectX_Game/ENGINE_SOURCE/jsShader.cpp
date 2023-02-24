#include "jsShader.h"
#include "jsGraphicDevice_DX11.h"

using namespace js::graphics;

namespace js
{
	Shader::Shader()
		: Resource(eResourceType::GraphicShader)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}
	Shader::~Shader()
	{
	}
	HRESULT Shader::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	void Shader::Create(graphics::eShaderStage stage, const std::wstring& file, const std::string& funcName)
	{
		mErrorBlob = nullptr;
				
		std::filesystem::path path = std::filesystem::current_path().parent_path();
		path += "\\SHADER_SOURCE\\";
		std::wstring shaderPath(path.c_str());
		shaderPath += file;

		if (eShaderStage::VS == stage)
		{
			D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
				, funcName.c_str(), "vs_5_0", 0, 0, mVSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

			if (mErrorBlob)
			{
				OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
				mErrorBlob->Release();
				mErrorBlob = nullptr;
			}

			GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer()
				, mVSBlob->GetBufferSize()
				, nullptr, mVS.GetAddressOf());

			if (mErrorBlob)
			{
				OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
				mErrorBlob->Release();
				mErrorBlob = nullptr;
			}
		}
		else
		{
			D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
				, funcName.c_str(), "ps_5_0", 0, 0, mPSBlob.GetAddressOf(), mErrorBlob.GetAddressOf());

			if (mErrorBlob)
			{
				OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
				mErrorBlob->Release();
				mErrorBlob = nullptr;
			}

			GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize()
				, nullptr, mPS.GetAddressOf());

			if (mErrorBlob)
			{
				OutputDebugStringA((char*)mErrorBlob->GetBufferPointer());
				mErrorBlob->Release();
				mErrorBlob = nullptr;
			}
		}
	}
	void Shader::Binds()
	{
		GetDevice()->BindPrimitiveTopology(mTopology);
		GetDevice()->BindInputLayout(mInputLayout.Get());
		GetDevice()->BindVertexShader(mVS.Get(), nullptr, 0);
		GetDevice()->BindPixelShader(mPS.Get(), nullptr, 0);
	}
}