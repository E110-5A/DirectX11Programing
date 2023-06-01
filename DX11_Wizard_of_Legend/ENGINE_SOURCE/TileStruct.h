#pragma once
#include "jsMath.h"
namespace js
{
	struct TileSet
	{
		math::Vector2 leftTop;		// 이미지 시작지점							index에 따라 다름
		math::Vector2 tileSize;		// 시작지점부터 잘라낼 가로 세로 픽셀 길이		32 x 32
		math::Vector2 tilesetSize;	// 텍스쳐 이미지 크기							? x ?
	public:
		TileSet()
			: leftTop(math::Vector2::Zero)
			, tileSize(math::Vector2::Zero)
			, tilesetSize(math::Vector2::Zero)
		{}
	};
	enum class eTileSet
	{
		Home,
		Air,
		Fire,
		Ice,
	};
	enum class eTileCollider
	{
		Wall,
		Platform,
		FallArea,
	};
}