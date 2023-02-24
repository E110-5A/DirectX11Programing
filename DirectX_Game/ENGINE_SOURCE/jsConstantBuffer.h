#pragma once
#include "jsGraphics.h"

namespace js::graphics
{
	class ConstantBuffer : public GPUBuffer
	{
	public:
		ConstantBuffer(eCBType type);
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void Bind(void* data);
		void SetPipline(eShaderStage stage);

	private:
		const eCBType mType;
	};
}