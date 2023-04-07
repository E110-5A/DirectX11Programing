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

		// ������ �����ð��� ���� �ð��� �Ѿ�� �������������� �̵�
		if (mSpriteSheet[mIndex].duration < mAddTime)
		{
			mAddTime = 0.0f;
			++mIndex;

			// �������� �ִ밹���� �����ϸ� �Ϸ�
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

		// �ؽ��� ���� ���� ��
		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		// �Է��� ��������Ʈ ������ŭ ����
		for (size_t spriteCount = 0; spriteCount < spriteLegth; ++spriteCount)
		{
			// API �ʹ� �ٸ��� 0~1 ������ ������ǥ�� ��ġ�� ǥ���ؾ��Ѵ�.
			Sprite sprite = {};

			// ������ǥ���� ��������Ʈ ũ�� * ���� ������ ��ŭ ���Ѱ��� �ؽ����� ���̷� ���� ������ ���Ѵ�
			sprite.leftTop = Vector2((leftTop.x + (spriteSize.x * (float)spriteCount)) / width, 
									(leftTop.y) / height) ;
			// ��������Ʈ ũ����� �ؽ����� ���̸�ŭ ���� ������ ���Ѵ�
			sprite.spriteSize = Vector2(spriteSize.x / width, spriteSize.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			// �ؽ��� ũ�� ���� ����
			sprite.atlasSize = Vector2(50.0f / width, 50.0f / height);

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::BindShader()
	{
		// �ؽ��ĸ� �������� 12�� ���Կ� ���ε�
		mAtlas->BindShader(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		// ���� ������� �ִϸ��̼��� ������ ������ ����
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