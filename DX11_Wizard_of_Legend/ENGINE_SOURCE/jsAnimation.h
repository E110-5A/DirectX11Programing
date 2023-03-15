#pragma once
#include "jsEntity.h"
#include "jsTexture.h"


namespace js
{
	using namespace math;
	using namespace graphics;

	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;		// 이미지 시작지점
			Vector2 spriteSize;		// 시작지점부터 잘라낼 가로 세로 픽셀 길이
			Vector2 offset;			// 렌더링 조정 좌표
			Vector2 atlasSize;		// 텍스쳐 이미지 크기
			float duration;			// 프레임 시간 간격
		
			Sprite()
				: leftTop(Vector2::Zero)
				, spriteSize(Vector2::Zero)
				, offset(Vector2::Zero)
				, atlasSize(Vector2::Zero)
				, duration(0.1f)
			{}
		};

		Animation();
		virtual ~Animation();

		UINT Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& name, 
					std::shared_ptr<Texture> atlas, 
					Vector2 leftTop, Vector2 spriteSize, Vector2 offset,
					UINT spriteLegth, float duration);
		void BindShader();
		void Reset();
		void Clear();

		bool IsComplete() { return mIsComplete; }
		std::wstring& AnimationName() { return mAnimationName; }

	private:
		class Aniamtor* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<Texture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mAddTime;
		bool mIsComplete;
	};
}