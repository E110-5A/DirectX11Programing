#pragma once
#include "CommonInclude.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"

#include "jsMesh.h"
#include "jsShader.h"
#include "jsConstantBuffer.h"

#include "jsCamera.h"

namespace js::renderer
{
	using namespace math;
	using namespace graphics;

	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
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
	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(FadeEffectCB, CBSLOT_FADE)
	{
		float	addTime;		// 누적시간
		float	duration;		// 효과 시간
		bool	fadeIn;			// In, Out 구분
	};

	extern Vertex vertexes[4];
	extern ConstantBuffer* constantBuffers[];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];
	
	extern std::vector<Camera*> cameras;

	void Initialize();
	void Render();
	void Release();
}

