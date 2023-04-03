#pragma once
#include "jsGraphics.h"

namespace js::graphics
{
	class StructuredBuffer : public GpuBuffer
	{
	public:
		StructuredBuffer();
		virtual ~StructuredBuffer();

		bool Create(eSRVType type, UINT size, UINT stride, void* data);
		void SetData(void* data, UINT bufferCount);
		void Bind(eShaderStage stage, UINT slot);

		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		eSRVType mType;

		UINT mSize;
		UINT mStride;
	};
}