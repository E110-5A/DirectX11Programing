#pragma once
#include "CommonInclude.h"
#include "jsMath.h"
#include "jsGraphicDevice_DX11.h"
#include "jsMesh.h"
#include "jsShader.h"
#include "jsConstantBuffer.h"
#include "jsCamera.h"
#include "jsFadeScript.h"
#include "jsLight.h"
#include "jsStructuredBuffer.h"

using namespace js::math;
using namespace js::graphics;

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

	CBUFFER(FadeCB, CBSLOT_FADE)
	{
		float alpha;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATION)
	{
		Vector2 leftTop;
		Vector2 spriteSize;
		Vector2 offset;
		Vector2 atlasSize;
		UINT	animationType;
	};

	CBUFFER(LightCB, CBSLOT_NUMBEROFLIGHT)
	{
		UINT numberOfLight;
	};

	CBUFFER(ParticleSystemCB, CBSLOT_PARTICLESYSTEM)
	{
		Vector4 worldPosition;
		Vector4 color;
		Vector4 size;

		UINT maxParticles;
		UINT simulationSpace;
		float radius;
		float speed;

		float lifeTime;
		float deltaTime;
		float elapsedTime;
		int padding;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 noiseSize;
	};

	extern Vertex vertexes[4];
	extern Camera* mainCamera;
	extern GameObject* mainCameraObject;
	extern FadeScript* fade;

	extern ConstantBuffer* constantBuffers[];
	extern StructuredBuffer* lightsBuffer;

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];
	
	extern std::vector<Camera*> cameras[];
	extern std::vector<DebugMesh> debugMeshes;
	extern std::vector<LightAttribute> lights;

	void Initialize();
	void Render();
	void Release();

	// Renderer
	void PushLightAttribute(LightAttribute lightAttribute);
	void BindLights();
	void BindNoiseTexture();
}