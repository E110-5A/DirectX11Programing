#pragma once
#include "jsEngine.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"

using namespace js::math;
using namespace js::graphics;

#define Triangle_Vertex 3
#define Rect_Vertex 4

#define NumOfInputLayout 2

namespace js::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};
	// 정점 데이터
	extern Vertex vertexes[Rect_Vertex];

	
	//버텍스 버퍼
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3D11Buffer* triangleIndexBuffer;
	extern ID3D11Buffer* triangleConstantBuffer;



	// 버텍스 셰이더
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVS;

	// 픽셀 셰이더
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePS;

	// input layout
	extern ID3D11InputLayout* triangleLayout;

	void Initialize();
	void Release();
}