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

		// �ִϸ��̼��� Complete �϶�, ���� �̺�Ʈ�� ȣ���ϰ� �����ΰ�� �ʱ�ȭ �����ش�
		if (mActiveAnimation->IsComplete())
		{
			if (events)
				events->mCompleteEvent();
			if (mIsLoop)
				mActiveAnimation->Reset();
		}
		
		// �ִϸ��̼��� �����ϰ�, ���� �ִϸ��̼��� ��������Ʈ �������� ��������
		UINT spriteIndex = mActiveAnimation->Update();

		if (events)
		{
		// Complete�� �ƴϰ�, ������ �߰��� ActionEvent�� �ִٸ� �װ��� ����
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

		// �̹� �ִ� �ִϸ��̼��̸� false ��ȯ
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
			return false;

		// �ִϸ��̼� ����
		animation = new Animation();
		animation->Create(name, atlas
			, leftTop, spriteSize, offset
			, spriteLegth, duration);

		// �ִϸ������� �ִϸ��̼� ��Ͽ� �߰�
		mAnimations.insert(std::make_pair(name, animation));

		// ActionEvents�� ��������Ʈ ������ ������ŭ �迭�� �ʱ�ȭ�Ͽ� �̺�Ʈ�� �߰��Ѵ� (�⺻: null �迭)
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
		// ���� �ִϸ��̼��� �ӽú����� �Ҵ�
		Animation* prevAnimation = mActiveAnimation;

		// endEvent�� �ִٸ� ȣ��
		Events* events = nullptr;
		if (prevAnimation)
			events = FindEvents(prevAnimation->AnimationName());
		if (events)
			events->mEndEvent();

		// ���� �ִϸ��̼� ����
		mActiveAnimation = FindAnimation(name);
		mActiveAnimation->Reset();
		mIsLoop = loop;

		// StartEvent�� �ִٸ� ȣ��
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