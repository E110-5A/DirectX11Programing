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
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	extern Vertex vertexes[Rect_Vertex];		
	extern Mesh* mesh;
	extern Shader* shader;
	extern ConstantBuffer* constantBuffers[];
		
	void Initialize();
	void Release();
}