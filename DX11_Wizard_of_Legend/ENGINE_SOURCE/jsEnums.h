#pragma once

namespace js::enums
{
	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Monster,
		Player,
		Effect,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		Collider,

		MeshRenerer,
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