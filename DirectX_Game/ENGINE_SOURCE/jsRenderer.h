#pragma once
#include "jsEngine.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"

#include "jsMesh.h"
#include "jsShader.h"
#include "jsConstantBuffer.h"

using namespace js::math;
using namespace js::graphics;

#define Triangle_Vertex 3
#define Rect_Vertex 4
#define NumOfInputLayout 3

namespace js::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Vector4 cbPosition;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	extern Vertex vertexes[Rect_Vertex];
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];

	void Initialize();
	void Release();
}