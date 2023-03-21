#include "jsAnimation.h"
#include "jsTime.h"
#include "jsRenderer.h"

namespace js
{
	Animation::Animation()
		: mAnimator(nullptr)
		, mAtlas(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mAddTime(0.0f)
		, mIsComplete(false)
	{
	}
	Animation::~Animation()
	{
	}

	UINT Animation::Update()
	{
		if (mIsComplete)
			return -1;

		mAddTime += Time::DeltaTime();

		// 프레임 유지시간이 누적 시간을 넘어서면 다음프레임으로 이동
		if (mSpriteSheet[mIndex].duration < mAddTime)
		{
			mAddTime = 0.0f;
			++mIndex;

			// 프레임이 최대갯수에 도달하면 완료
			if (mSpriteSheet.size() <= mIndex)
			{
				mIsComplete = true;
				mIndex = int(mSpriteSheet.size() - 1);
			}
			return mIndex;
		}
		return -1;
	}
	void Animation::FixedUpdate()
	{
	}

	void Animation::Render()
	{
	}

	void Animation::Create(const std::wstring& name
		, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 spriteSize, Vector2 offset
		, UINT spriteLegth, float duration)
	{
		mAnimationName = name;
		mAtlas = atlas;

		// 텍스쳐 가로 세로 값
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		// 입력한 스프라이트 개수만큼 생성
		for (size_t spriteCount = 0; spriteCount < spriteLegth; ++spriteCount)
		{
			// API 와는 다르게 0~1 사이의 비율좌표로 위치를 표현해야한다.
			Sprite sprite = {};

			// 시작좌표에서 스프라이트 크기 * 현재 프레임 만큼 더한값을 텍스쳐의 길이로 나눠 비율을 구한다
			sprite.leftTop = Vector2((leftTop.x + (spriteSize.x * (float)spriteCount)) / width, 
									(leftTop.y) / height) ;
			// 스프라이트 크기또한 텍스쳐의 길이만큼 나눠 비율을 구한다
			sprite.spriteSize = Vector2(spriteSize.x / width, spriteSize.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			// 텍스쳐 크기 비율 조절
			sprite.atlasSize = Vector2(50.0f / width, 50.0f / height);

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::BindShader()
	{
		// 텍스쳐를 레지스터 12번 슬롯에 바인딩
		mAtlas->BindShader(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		// 현재 재생중인 애니메이션의 프레임 정보를 전달
		renderer::AnimationCB info = {};
		info.animationType = (UINT)eAnimationType::SecondDimension;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.spriteSize = mSpriteSheet[mIndex].spriteSize;
		info.atlasSize = mSpriteSheet[mIndex].atlasSize;

		cb->Bind(&info);
		cb->SetPipline(eShaderStage::PS);
	}

	void Animation::Reset()
	{
		mAddTime = 0.0f;
		mIndex = 0;
		mIsComplete = false;
	}

	void Animation::Clear()
	{
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB info = {};
		info.animationType = (UINT)eAnimationType::None;

		cb->Bind(&info);
		cb->SetPipline(eShaderStage::PS);
	}
}