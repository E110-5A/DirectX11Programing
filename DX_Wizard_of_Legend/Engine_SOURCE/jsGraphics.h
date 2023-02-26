#pragma once
#include <wrl.h>

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include "jsMath.h"

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM 0
#define CBSLOT_MATERIAL 1
#define CBSLOT_GRID 2

namespace js::graphics
{
	enum class ValidationMode
	{
		Disabled,
		Enabled,
		GPU,
	};

	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		Count,
	};

	enum class eSamplerType
	{
		Point,
		Linear,
		Anisotropic,
		End,
	};
	enum class eRSType
	{
		SolidBack,		// 뒷면 X
		SolidFront,		// 앞면 X
		SolidNone,		// 상관없이 그림
		WireframeNone,	// 뼈대만 그림
		End,
	};
	enum class eDSType
	{
		Less,			// 작거나 같으면 덮어씀
		Greater,		// 크면 덮어 씀
		NoWrite,		// 작으면 덮어쓰지 않음
		None,			// 깊이값 사용안함
		End,
	};
	enum class eBSType
	{
		Default,		//
		AlphaBlend,		//
		OneOne,			//
		End,
	};

	enum class eRenderingMode
	{
		Opaque,			// 투명 영역이 없음
		Cutout,			// 경계면을 처리하는 영역?
		Transparent,	// 투명
		End,
	};

	struct GpuBuffer
	{
		enum class eType
		{
			Buffer,
			Texture,
			UnknownType,
		} type = eType::UnknownType;

		D3D11_BUFFER_DESC desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

		GpuBuffer() = default;
		virtual ~GpuBuffer() = default;
	};

	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		End,
	};
	enum class eGPUParam
	{
		Int,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Matrix,
	};
}