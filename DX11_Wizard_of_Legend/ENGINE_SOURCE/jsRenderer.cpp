#include "jsRenderer.h"
#include "jsResources.h"
#include "jsMaterial.h"
#include "jsSceneManager.h"
#include "jsPaintShader.h"
#include "jsParticleShader.h"
#include "jsGameObject.h"
#include "jsPlayerScript.h"

namespace js::renderer
{
	Vertex vertexes[4] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};
	
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	StructuredBuffer* lightsBuffer = nullptr;

	Camera* mainCamera = nullptr;
	Camera* uiCamera = nullptr;
	GameObject* mainCameraObject = nullptr;
	FadeScript* fade = nullptr;
	PlayerScript* player = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;

	void LoadMesh()
	{
#pragma region Create PointMesh
		Vertex point = {};
		std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"PointMesh", pointMesh);
		pointMesh->CreateVertexBuffer(&point, 1);
		UINT pointIndex = 0;
		pointMesh->CreateIndexBuffer(&pointIndex, 1);
#pragma endregion

#pragma region Create RectMesh

		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		std::shared_ptr<Mesh> rectMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", rectMesh);

		rectMesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);

		rectMesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());
#pragma endregion
#pragma region Create DebugRectMesh
		
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		std::shared_ptr<Mesh> debugRectMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugRectMesh);
		debugRectMesh->CreateVertexBuffer(vertexes, 4);
		debugRectMesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());
		
#pragma endregion
#pragma region Create DebugCircleMesh

		std::vector<Vertex> circleVertexs;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.00001f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVertexs.push_back(center);

		int iSlice = 80;
		float fRadius = 0.5;
		float fTheta = XM_2PI / (float)iSlice;

		for (size_t point = 0; point < iSlice; ++point)
		{
			Vertex vtx = {};
			vtx.pos = Vector4
			(
				fRadius * cosf(fTheta * (float)point)
				, fRadius * sinf(fTheta * (float)point)
				, -0.00001f, 1.0f
			);
			vtx.color = center.color;

			circleVertexs.push_back(vtx);
		}
		indexes.clear();
		for (size_t point = 0; point < static_cast<unsigned long long>(iSlice) - 2; ++point)
		{
			indexes.push_back(UINT(point + 1));
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> debugCircleMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugCircleMesh", debugCircleMesh);
		debugCircleMesh->CreateVertexBuffer(circleVertexs.data(), (UINT)circleVertexs.size());
		debugCircleMesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());

#pragma endregion
	}

	void SetUpState()
	{
#pragma region Input layout
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;


		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiShader->GetVSBlobBufferPointer()
			, uiShader->GetVSBlobBufferSize()
			, uiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> fadeShader = Resources::Find<Shader>(L"FadeShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, fadeShader->GetVSBlobBufferPointer()
			, fadeShader->GetVSBlobBufferSize()
			, fadeShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, debugShader->GetVSBlobBufferPointer()
			, debugShader->GetVSBlobBufferSize()
			, debugShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, particleShader->GetVSBlobBufferPointer()
			, particleShader->GetVSBlobBufferSize()
			, particleShader->GetInputLayoutAddressOf());

#pragma endregion
#pragma region sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		//D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
		//D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;


		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point
			, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear
			, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic
			, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer state
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());


#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		
		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::None].GetAddressOf());
		
#pragma endregion
#pragma region Blend State

		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;

		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadBuffer()
	{
#pragma region Constant Buffers

		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Fade] = new ConstantBuffer(eCBType::Fade);
		constantBuffers[(UINT)eCBType::Fade]->Create(sizeof(FadeCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		constantBuffers[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
		constantBuffers[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));

		constantBuffers[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

#pragma endregion
#pragma region Structured Buffers

		lightsBuffer = new StructuredBuffer();
		lightsBuffer->Create(eSRVType::SRV, sizeof(LightAttribute), 128, nullptr, true);
#pragma endregion
	}

	void LoadShader()
	{
#pragma region Default Triangle Shader
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		Resources::Insert<Shader>(L"RectShader", shader);
#pragma endregion

#pragma region Sprite
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		Resources::Insert<Shader>(L"SpriteShader", spriteShader);
#pragma endregion
#pragma region UI
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");
		Resources::Insert<Shader>(L"UIShader", uiShader);
#pragma endregion
#pragma region Grid Shader
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);
		Resources::Insert<Shader>(L"GridShader", gridShader);
#pragma endregion
#pragma region Fade Shader
		std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
		fadeShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		fadeShader->Create(eShaderStage::PS, L"FadePS.hlsl", "main");
		Resources::Insert<Shader>(L"FadeShader", fadeShader);
#pragma endregion
#pragma region Debug Shader
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		Resources::Insert<Shader>(L"DebugShader", debugShader);
#pragma endregion
#pragma region PaintShader
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Resources::Insert<PaintShader>(L"PaintShader", paintShader);
#pragma endregion
#pragma region ParticleShader
		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		Resources::Insert<Shader>(L"ParticleShader", particleShader);

		std::shared_ptr<ParticleShader> particleCS = std::make_shared<ParticleShader>();
		Resources::Insert<ParticleShader>(L"ParticleCS", particleCS);
		particleCS->Create(L"ParticleCS.hlsl", "main");
#pragma endregion
	}

	void LoadTexture()
	{
#pragma region Sample
		Resources::Load<Texture>(L"DefaultSprite", L"DefaultSprite.png");
		Resources::Load<Texture>(L"CartoonSmoke", L"particle\\CartoonSmoke.png");
		Resources::Load<Texture>(L"noise_01", L"noise\\noise_01.png");
		Resources::Load<Texture>(L"noise_02", L"noise\\noise_02.png");

#pragma endregion
#pragma region DYNAMIC Texture
		// Paint
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert<Texture>(L"PaintTexture", uavTexture);


#pragma endregion
#pragma region STATIC Texture

		// Stage
		Resources::Load<Texture>(L"HomeStage", L"homeStage.png");


		// LogoScene
		Resources::Load<Texture>(L"LogoTexture", L"BackGround\\Logo.png");
		Resources::Load<Texture>(L"MousePointer", L"Crosshair.png");
		// TitleScene
		Resources::Load<Texture>(L"TitleTexture", L"BackGround\\TitleLogo.png");
		Resources::Load<Texture>(L"TitleBackGround", L"BackGround\\TitleBackground.png");
		// PlayScene
		Resources::Load<Texture>(L"PlayBackGround", L"testBackground.png");
		// HUD
		Resources::Load<Texture>(L"HealthHUD", L"UI\\HealthHUD.bmp");
		Resources::Load<Texture>(L"SkillHUD", L"UI\\SkillHUD.bmp");
		// Object

		// Projectile
		Resources::Load<Texture>(L"WindSlash", L"Player\\Arcana\\WindSlash.png");
		Resources::Load<Texture>(L"FireArrow", L"Player\\Arcana\\FireArrow.png");
		Resources::Load<Texture>(L"DragonArc", L"Player\\Arcana\\DragonArc.png");
		
#pragma endregion
	}

	void LoadMaterial()
	{
#pragma region sample
		std::shared_ptr<Material> paintMaterial = std::make_shared<Material>();
		paintMaterial->SetRenderingMode(eRenderingMode::Transparent);
		paintMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"PaintTexture"));
		paintMaterial->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		Resources::Insert<Material>(L"RectMaterial", paintMaterial);

		// Sprite
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		spriteMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"DefaultSprite"));
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);

#pragma endregion

#pragma region UI
		std::shared_ptr<Material> healthHUDMaterial = std::make_shared<Material>();
		healthHUDMaterial->SetRenderingMode(eRenderingMode::Transparent);
		healthHUDMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"HealthHUD"));
		healthHUDMaterial->SetShader(Resources::Find<Shader>(L"UIShader"));
		Resources::Insert<Material>(L"HealthHUDMaterial", healthHUDMaterial);

		std::shared_ptr<Material> skillHUDMaterial = std::make_shared<Material>();
		skillHUDMaterial->SetRenderingMode(eRenderingMode::Transparent);
		skillHUDMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"SkillHUD"));
		skillHUDMaterial->SetShader(Resources::Find<Shader>(L"UIShader"));
		Resources::Insert<Material>(L"SkillHUDMaterial", skillHUDMaterial);


#pragma endregion

#pragma region Grid
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetRenderingMode(eRenderingMode::Transparent);
		gridMaterial->SetShader(Resources::Find<Shader>(L"GridShader"));
		Resources::Insert<Material>(L"GridMaterial", gridMaterial);

#pragma endregion

#pragma region Fade
		std::shared_ptr<Material> fadeMaterial = std::make_shared<Material>();
		fadeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		fadeMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"DefaultSprite"));
		fadeMaterial->SetShader(Resources::Find<Shader>(L"FadeShader"));
		Resources::Insert<Material>(L"FadeMaterial", fadeMaterial);

#pragma endregion

#pragma region Debug
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(Resources::Find<Shader>(L"DebugShader"));
		Resources::Insert<Material>(L"DebugMaterial", debugMaterial);

#pragma endregion

#pragma region Particle
		std::shared_ptr<Material> particleMaterial = std::make_shared<Material>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(Resources::Find<Shader>(L"ParticleShader"));
		//particleMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"CartoonSmoke"));
		Resources::Insert<Material>(L"ParticleMaterial", particleMaterial);

#pragma endregion

#pragma region Logo
		std::shared_ptr<Material> logoMaterial = std::make_shared<Material>();
		logoMaterial->SetRenderingMode(eRenderingMode::Transparent);
		logoMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"LogoTexture"));
		logoMaterial->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		Resources::Insert<Material>(L"LogoMaterial", logoMaterial);

#pragma endregion
#pragma region Title Logo
		std::shared_ptr<Material> titleMaterial = std::make_shared<Material>();
		titleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		titleMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"TitleTexture"));
		titleMaterial->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		Resources::Insert<Material>(L"TitleMaterial", titleMaterial);
#pragma endregion

#pragma region Title Background
		std::shared_ptr<Material> titleBGMaterial = std::make_shared<Material>();
		titleBGMaterial->SetRenderingMode(eRenderingMode::Transparent);
		titleBGMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"TitleBackGround"));
		titleBGMaterial->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		Resources::Insert<Material>(L"TitleBGMaterial", titleBGMaterial);
#pragma endregion

#pragma region Background
		std::shared_ptr<Material> BGMaterial = std::make_shared<Material>();
		BGMaterial->SetRenderingMode(eRenderingMode::Transparent);
		BGMaterial->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		Resources::Insert<Material>(L"BGMaterial", BGMaterial);

#pragma endregion
#pragma region Mouse Pointer
		std::shared_ptr<Material> mouseMaterial = std::make_shared<Material>();
		mouseMaterial->SetRenderingMode(eRenderingMode::Transparent);
		mouseMaterial->SetTexture(eTextureSlot::T0, Resources::Find<Texture>(L"MousePointer"));
		mouseMaterial->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		Resources::Insert<Material>(L"MouseMaterial", mouseMaterial);
#pragma endregion

#pragma region Animation GameObject
		std::shared_ptr<Material> objectMaterial = std::make_shared<Material>();
		objectMaterial->SetRenderingMode(eRenderingMode::Transparent);
		objectMaterial->SetShader(Resources::Find<Shader>(L"SpriteShader"));
		Resources::Insert<Material>(L"ObjectMaterial", objectMaterial);
#pragma endregion

	}

	void Initialize()
	{		
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i]; 
			constantBuffers[i] = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		// 현재 씬에 있는 카메라 가져옴
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
		lights.clear();
	}

	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		// 버퍼 바인드 및 파이프라인 연결
		lightsBuffer->SetData(lights.data(), (UINT)lights.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);

		// light개수 넘기기
		LightCB lightCB = {};
		lightCB.numberOfLight = (UINT)lights.size();

		ConstantBuffer* cb = constantBuffers[(UINT)eCBType::Light];
		cb->SetData(&lightCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> noise = Resources::Find<Texture>(L"noise_01");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = (float)noise->GetWidth();
		info.noiseSize.y = (float)noise->GetHeight();

		ConstantBuffer* cb = constantBuffers[(UINT)eCBType::Noise];
		cb->SetData(&info);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}
}