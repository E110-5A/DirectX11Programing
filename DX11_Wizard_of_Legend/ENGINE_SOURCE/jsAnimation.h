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
			Vector2 leftTop;		// �̹��� ��������
			Vector2 spriteSize;		// ������������ �߶� ���� ���� �ȼ� ����
			Vector2 offset;			// ������ ���� ��ǥ
			Vector2 atlasSize;		// �ؽ��� �̹��� ũ��
			float duration;			// ������ �ð� ����
		
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