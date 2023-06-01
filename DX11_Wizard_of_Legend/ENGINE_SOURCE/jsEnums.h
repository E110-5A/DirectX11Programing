#pragma once

namespace js::enums
{
	enum class eSceneType
	{
		Logo,
		Title,
		Home,
		Stage01,
		Stage01Boss,
		Stage02,
		Stage02Boss,
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
		Trap,
		ENV,
		Platform,
		FallArea,
		Monster,
		MonsterProjectile,
		Player,
		PlayerProjectile,

		Particle,
		UI,
		End,
	};

	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		Collider,
		Rigidbody,
		Tile,
		TileRenderer,
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
		Directional,	// 전체
		Point,			// 구 범위
		Spot,			// 방사형
		End,
	};




	
}