#include "jsRenderer.h"

namespace js::renderer
{	
	Vertex vertexes[Rect_Vertex] = {};
		
	ID3DBlob* errorBlob = nullptr;
	ID3D11Buffer* triangleBuffer = nullptr;
	ID3D11Buffer* triangleIndexBuffer = nullptr;
	ID3D11Buffer* triangleConstantBuffer = nullptr;



	ID3DBlob* triangleVSBlob = nullptr;
	ID3D11VertexShader* triangleVS = nullptr;
		
	ID3DBlob* trianglePSBlob = nullptr;
	ID3D11PixelShader* trianglePS = nullptr;
		
	ID3D11InputLayout* triangleLayout = nullptr;

	void SetUpState()
	{
		// Input Layout
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[NumOfInputLayout] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 12;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		GetDevice()->CreateInputLayout(arrLayoutDesc, 2
			, triangleVSBlob->GetBufferPointer()
			, triangleVSBlob->GetBufferSize()
			, &triangleLayout);
	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.ByteWidth = sizeof(Vertex) * Rect_Vertex;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;

		GetDevice()->CreateBuffer(&triangleDesc, &triangleData, &triangleBuffer);





		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		D3D11_BUFFER_DESC indexDesc = {};
		indexDesc.ByteWidth = indexes.size() * sizeof(UINT);
		indexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		indexDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		indexDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA indexData = {};
		indexData.pSysMem = indexes.data();

		GetDevice()->CreateBuffer(&indexDesc, &indexData, &triangleIndexBuffer);





		D3D11_BUFFER_DESC constantDesc = {};
		constantDesc.ByteWidth = sizeof(Vector4);
		constantDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		constantDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		constantDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				
		GetDevice()->CreateBuffer(&constantDesc, nullptr, &triangleConstantBuffer);

		Vector4 testConstant(0.2f, 0.2f, 0.f, 0.f);
		GetDevice()->BindConstantBuffer(triangleConstantBuffer, &testConstant, sizeof(Vector4));
	}

	void LoadShader()
	{
		GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.5f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.5f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.5f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.5f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);

		LoadShader();
		SetUpState();
		LoadBuffer();
	}

	void Release()
	{
		triangleBuffer->Release();

		triangleIndexBuffer->Release();
		triangleConstantBuffer->Release();

		triangleVSBlob->Release();
		triangleVS->Release();

		trianglePSBlob->Release();
		trianglePS->Release();

		triangleLayout->Release();
	}
}