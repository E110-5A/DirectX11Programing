#pragma once

namespace js::enums
{
	enum class eSceneType
	{
		Logo,
		Title,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Background,
		Tile,
		Wall,
		Platform,
		FallArea,
		Monster,
		MonsterProjectile,
		Player,
		PlayerProjectile,

		Particle,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		Collider,
		Rigidbody,
		MeshRenerer,
		SpriteRenderer,
		Animator,
		ParticleSystem,
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