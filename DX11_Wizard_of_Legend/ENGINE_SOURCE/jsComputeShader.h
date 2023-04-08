#pragma once
#include "jsGraphics.h"
#include "jsResource.h"

namespace js::graphics
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader();
		ComputeShader(UINT threadGroupX, UINT threadGroupY, UINT threadGroupZ);
		virtual ~ComputeShader();

		virtual HRESULT Load(const std::wstring& path) override;

		virtual void Binds();
		virtual void Clear();

		bool Create(const std::wstring& file, const std::string& funcName);
		void OnExcute();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;

		UINT mThreadGroupCountX;
		UINT mThreadGroupCountY;
		UINT mThreadGroupCountZ;

		UINT mGroupX;
		UINT mGroupY;
		UINT mGroupZ;
	};
}