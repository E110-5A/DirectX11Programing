#pragma once
#include "jsComponent.h"
namespace js
{
	// 뭐를 상속받는지 모르겠음.. 아마 스크립트? 아니면 컴포넌트?
	// 자세한건 유니티를 참고해서 만들면 될거같긴 함

	/* 내생각에는
* 타일이 이미지랑 충돌타입, 배경 오브젝트  이런걸 가지고 렌더링 돌려주는? 상상해봄
*
* 타일을 배열로 관리하면서 2차원 배열로 쫙 깔린 다음에 타일맵 객체가 일괄적으로 관리할 수 있도록
* 타일 배치에 그리드 개념도 적용해서 하고싶음
*/

	// 그리드 객체는 사실 없어도 무방할듯 함
	struct TileGrid
	{
		float			size;
		math::Vector2	location;		// (1,1)  (2,3) 이런식으로 깔리게 됨
	};

	class Tile : public Component
	{
	public:
		Tile();
		virtual ~Tile();

		// 타일에 적용되는 기본적인 기능 함수
		void TileGridProcess();

		// 이미지 렌더링하는 함수

		// 이미지 세팅하는 함수

		// 충돌 판정?도 해야하나?


	private:

	};
}


