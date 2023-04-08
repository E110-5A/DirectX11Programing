#pragma once
#include "jsGraphics.h"

using namespace js::enums;

namespace js::graphics
{
	class ConstantBuffer : GpuBuffer
	{
	public:
		ConstantBuffer(eCBType type);
		virtual ~ConstantBuffer();

		bool Create(size_t size);
		void SetData(void* data);
		void Bind(eShaderStage stage);


	private:
		const eCBType mType;
	};
}
