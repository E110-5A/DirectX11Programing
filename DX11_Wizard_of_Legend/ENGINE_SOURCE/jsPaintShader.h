#pragma once
#include "jsComputeShader.h"
#include "jsTexture.h"

namespace js::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		PaintShader();
		virtual ~PaintShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<Texture> texture) { mTarget = texture; }

	private:
		std::shared_ptr<Texture> mTarget;
	};
		
}