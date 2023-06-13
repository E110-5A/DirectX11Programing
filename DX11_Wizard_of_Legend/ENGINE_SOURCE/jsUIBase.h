#pragma once
#include "jsEntity.h"

// 쓸지 안쓸지 모르겠음
#include "jsTexture.h"
#include "jsMaterial.h"


namespace js
{
	class Image;
	class GameObject;
	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				// 함수는 r-value(코드영역)이기 때문에 move를 통해서 옮겨줘야함
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		UIBase(eUIType type);
		virtual ~UIBase();

		void Initialize();			//	UI가 로드될 때 호출되는 초기화 함수
		void Active();				//	UI가 활성화 되면 호출되는 함수
		void InActive();			//	UI가 비활성화 되면 호출되는 함수
		void Tick();				//	UI가 업데이트 될 때마다 호출되는 함수
		void Render(HDC hdc);
		void UIClear();				//	UI가 사라질 때 호출되는 함수

		void AddChild(UIBase* uiBase);


		eUIType GetType() { return mType; }
		void SetParent(UIBase* parent) { mParent = parent; }

		// 이미지 관련 내용은 dx11에 맞게 수정해야함



	protected:
		virtual void OnInit() {};
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnTick() {};
		virtual void OnRender(HDC hdc) {};
		virtual void OnClear() {};
				
		UIBase* mParent;
		
	protected:
		// 아마도 컴포넌트들 가지고 있으면 좋을듯?
		// Tr, Renderer, Script..?

	private:
		std::vector<UIBase*> mChilds;
		eUIType mType;
		bool	mIsEnable;
	};
}