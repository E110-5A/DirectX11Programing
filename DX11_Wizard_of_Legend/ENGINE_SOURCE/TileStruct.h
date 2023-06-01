#pragma once
#include "jsMath.h"
namespace js
{
	struct TileSet
	{
		math::Vector2 leftTop;		// �̹��� ��������							index�� ���� �ٸ�
		math::Vector2 tileSize;		// ������������ �߶� ���� ���� �ȼ� ����		32 x 32
		math::Vector2 tilesetSize;	// �ؽ��� �̹��� ũ��							? x ?
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