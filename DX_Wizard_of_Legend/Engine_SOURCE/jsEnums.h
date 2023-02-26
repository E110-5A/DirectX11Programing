#pragma once

namespace js::enums
{


	enum class eLayerType
	{
		None = 0,
		Camera,
		Effect,
		Grid,
		Monster,
		Player,

		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		Mesh,
		Collider,
		
		MeshRenderer,
		SpriteRenderer,

		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

}