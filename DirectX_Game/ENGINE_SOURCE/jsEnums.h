#pragma once

namespace js::enums
{
	enum class eLayerType
	{
		None,
		Camera,
		Monster,
		Player,
		End = 15,
	};
		
	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		Mesh,
		Collider,
		UI,
		Script,
		End = 15,
	};
}