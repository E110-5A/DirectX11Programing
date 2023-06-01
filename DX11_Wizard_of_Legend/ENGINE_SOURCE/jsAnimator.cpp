#include "jsAnimator.h"

namespace js
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mActiveAnimation(nullptr)
		, mIsLoop(false)
	{
	}
	Animator::~Animator()
	{
		for (auto anim : mAnimations)
		{
			delete anim.second;
			anim.second = nullptr;
		}

		for (auto evt : mEvents)
		{
			delete evt.second;
			evt.second = nullptr;
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;

		Events* events = FindEvents(mActiveAnimation->AnimationName());

		// 애니메이션이 Complete 일때, 관련 이벤트를 호출하고 루프인경우 초기화 시켜준다
		if (mActiveAnimation->IsComplete())
		{
			if (events)
				events->mCompleteEvent();
			if (mIsLoop)
				mActiveAnimation->Reset();
		}
		
		// 애니메이션을 실행하고, 현재 애니메이션의 스프라이트 프레임을 가져오기
		UINT spriteIndex = mActiveAnimation->Update();

		if (events)
		{
		// Complete가 아니고, 프레임 중간에 ActionEvent가 있다면 그것을 실행
			if (spriteIndex != -1
				&& events->mActionEvents[spriteIndex].mEvent)
			{
				events->mActionEvents[spriteIndex].mEvent();
			}
		}		
	}

	void Animator::FixedUpdate()
	{
	}
	void Animator::Render()
	{
	}

	bool Animator::Create(const std::wstring& name, std::shared_ptr<Texture> atlas
		, Vector2 leftTop, Vector2 spriteSize, Vector2 offset
		, UINT spriteLegth, float duration)
	{
		if (atlas == nullptr)
			return false;

		// 이미 있는 애니메이션이면 false 반환
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return false;

		// 애니메이션 생성
		animation = new Animation();
		animation->Create(name, atlas
			, leftTop, spriteSize, offset
			, spriteLegth, duration);

		// 애니메이터의 애니메이션 목록에 추가
		mAnimations.insert(std::make_pair(name, animation));

		// ActionEvents를 스프라이트 프레임 개수만큼 배열로 초기화하여 이벤트에 추가한다 (기본: null 배열)
		Events* events = new Events();
		events->mActionEvents.resize(spriteLegth);
		mEvents.insert(std::make_pair(name, events));

		return true;
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}

	void Animator::Play(const std::wstring& name, bool loop)
	{
		// 현재 애니메이션을 임시변수에 할당
		Animation* prevAnimation = mActiveAnimation;

		// endEvent가 있다면 호출
		Events* events = nullptr;
		if (prevAnimation)
			events = FindEvents(prevAnimation->AnimationName());
		if (events)
			events->mEndEvent();

		// 다음 애니메이션 실행
		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mIsLoop = loop;

		// StartEvent가 있다면 호출
		events = FindEvents(mActiveAnimation->AnimationName());
		if (events)
			events->mStartEvent();
	}

	void Animator::Binds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->BindShader();
	}

	void Animator::Clear()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->Clear();
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);

		return events->mEndEvent.mEvent;
	}
	std::function<void()>& Animator::GetActionEvent(const std::wstring& name, UINT index)
	{
		Events* events = FindEvents(name);

		return events->mActionEvents[index].mEvent;
	}
}