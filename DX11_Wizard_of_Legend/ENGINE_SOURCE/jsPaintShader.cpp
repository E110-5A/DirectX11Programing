#include "jsPaintShader.h"

namespace js::graphics
{
	PaintShader::PaintShader()
		: mTarget(nullptr)
	{
	}
	PaintShader::~PaintShader()
	{
	}
	void PaintShader::Binds()
	{
		mTarget->BindUnorderedAccessView(0);

		mGroupX = (UINT)mTarget->GetWidth() / mThreadGroupCountX + 1;
		mGroupY = (UINT)mTarget->GetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}
	void PaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessView(0);
	}
}