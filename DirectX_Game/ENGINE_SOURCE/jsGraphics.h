#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include "jsMath.h"

namespace js::graphics
{
	enum class ValidationMode
	{
		Disabled,
		Enable,
		GPU,
	};

	enum class eCBType
	{
		None,
		Transform,
		Material,
		End,
	};
	
	enum class eShaderStage
	{
		VS,		// Vertex Shader
		HS,		// Hull Shader
		DS,		// Domain Shader
		GS,		// Geometry Shader
		PS,		// Pixel Shader
		CS,		// Compute shader
		Count,
	};	
}