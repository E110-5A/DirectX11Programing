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
		void Bind(void* data);
		void SetPipline(eShaderStage stage);

		//void SetType(eCBType type) { mType = type; }


	private:
		const eCBType mType;
	};
}
