#include "jsStructuredBuffer.h"
#include "jsGraphicDevice_DX11.h"

namespace js::graphics
{
	StructuredBuffer::StructuredBuffer()
		: mSRV(nullptr)
		, mType(eSRVType::SRV)
		, mSize(0)
		, mStride(0)
		, mSRVSlot(-1)
		, mUAVSlot(-1)
	{
	}
	StructuredBuffer::~StructuredBuffer()
	{
	}


	bool StructuredBuffer::Create(eSRVType type, UINT size, UINT stride, void* data)
	{
		mType = type;
		mSize = size;
		mStride = stride;

		desc.ByteWidth = mSize * mStride;
		desc.StructureByteStride = mSize;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		if (eSRVType::UAV == mType)
		{
			desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;
			desc.CPUAccessFlags = 0;
		}

		// 버퍼 생성
		if (data)
		{
			D3D11_SUBRESOURCE_DATA sub = {};
			sub.pSysMem = data;

			if (!(GetDevice()->CreateBuffer(&desc, &sub, buffer.GetAddressOf())))
				return false;
		}
		else
		{
			if (!(GetDevice()->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
				return false;
		}
		
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;

		if (!(GetDevice()->CreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
			return false;



		if (eSRVType::UAV == mType)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
			uavDesc.Buffer.NumElements = mStride;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			if (!(GetDevice()->CreateUnorderedAccessView(buffer.Get(), &uavDesc, mUAV.GetAddressOf())))
				return false;
		}


		return true;
	}
	void StructuredBuffer::SetData(void* data, UINT bufferCount)
	{
		if (mStride < bufferCount)
		{
			Create(eSRVType::SRV, mSize, bufferCount, data);
		}
		else
		{
			GetDevice()->BindBuffer(buffer.Get(), data, mSize * bufferCount);
		}
	}
	void StructuredBuffer::BindSRV(eShaderStage stage, UINT slot)
	{
		GetDevice()->BindShaderResource(stage, slot, mSRV.GetAddressOf());
	}
	void StructuredBuffer::BindUAV(eShaderStage stage, UINT slot)
	{
		UINT i = -1;
		GetDevice()->BindUnorderedAccessView(slot, 1, mUAV.GetAddressOf(), &i);
	}
	void StructuredBuffer::Clear()
	{
		ID3D11ShaderResourceView* srv = nullptr;
		GetDevice()->BindShaderResource(eShaderStage::VS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, mSRVSlot, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, mSRVSlot, &srv);

		ID3D11UnorderedAccessView* uav = nullptr;
		UINT i = -1;
		GetDevice()->BindUnorderedAccessView(mUAVSlot, 1, &uav, &i);
	}
}