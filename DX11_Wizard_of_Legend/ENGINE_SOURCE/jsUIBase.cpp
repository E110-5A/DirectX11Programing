#include "jsUIBase.h"
#include "jsResources.h"
#include "jsGameObject.h"

namespace js
{
	UIBase::UIBase(eUIType type)
		: mType(type)
		, mIsEnable(false)
		, mParent(nullptr)
	{
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		OnInit();

		for (UIBase* child : mChilds)
		{
			child->OnInit();
		}
	}

	void UIBase::Active()
	{
		mIsEnable = true;
		OnActive();
		for (UIBase* child : mChilds)
		{
			child->mIsEnable = true;
			child->Active();
		}
	}

	void UIBase::InActive()
	{
		mIsEnable = false;
		for (UIBase* child : mChilds)
		{
			child->OnInActive();
			child->mIsEnable = false;
		}
		OnInActive();
		mIsEnable = false;
	}

	void UIBase::Tick()
	{
		if (false == mIsEnable)
			return;
		OnTick();

		// child 설정 (추후에 변경해야함)
		/*if (mParent)
			mScreenPos = mParent->GetPos() + mPos;
		else
			mScreenPos = mPos;*/

		for (UIBase* child : mChilds)
		{
			if (child->mIsEnable)
				child->Tick();
		}
	}

	void UIBase::Render(HDC hdc)
	{
		if (false == mIsEnable)
			return;
		OnRender(hdc);
		for (UIBase* child : mChilds)
		{
			if (child->mIsEnable)
				child->Render(hdc);
		}
	}

	void UIBase::UIClear()
	{
		for (UIBase* child : mChilds)
		{
			if (child->mIsEnable)
				child->UIClear();
		}
		OnClear();
	}
	
	void UIBase::AddChild(UIBase* uiBase)
	{
		mChilds.push_back(uiBase);
		uiBase->mParent = this;
	}
}