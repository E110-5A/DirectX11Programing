#pragma once

namespace js::enums
{
	enum class eSceneType
	{
		Title,

		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Tile,
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
		MeshRenerer,
		SpriteRenderer,
		Animator,
		Light,
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

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}