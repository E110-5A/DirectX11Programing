#pragma once
#include "jsEngine.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"

#include "jsMesh.h"

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

	
	// mesh
	extern Mesh* mesh;

	extern Microsoft::WRL::ComPtr<ID3DBlob>				errorBlob;
	extern Microsoft::WRL::ComPtr<ID3D11Buffer>			triangleConstantBuffer;
	
	// shader
	extern Microsoft::WRL::ComPtr<ID3DBlob>				triangleVSBlob;
	extern Microsoft::WRL::ComPtr<ID3D11VertexShader>	triangleVS;
	extern Microsoft::WRL::ComPtr<ID3DBlob>				trianglePSBlob;
	extern Microsoft::WRL::ComPtr<ID3D11PixelShader>	trianglePS;

	// input layout
	extern Microsoft::WRL::ComPtr<ID3D11InputLayout>	triangleLayout;

	void Initialize();
	void Release();
}