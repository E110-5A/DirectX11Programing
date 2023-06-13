#pragma once
#include "jsEntity.h"

// ���� �Ⱦ��� �𸣰���
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
				// �Լ��� r-value(�ڵ念��)�̱� ������ move�� ���ؼ� �Ű������
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

		void Initialize();			//	UI�� �ε�� �� ȣ��Ǵ� �ʱ�ȭ �Լ�
		void Active();				//	UI�� Ȱ��ȭ �Ǹ� ȣ��Ǵ� �Լ�
		void InActive();			//	UI�� ��Ȱ��ȭ �Ǹ� ȣ��Ǵ� �Լ�
		void Tick();				//	UI�� ������Ʈ �� ������ ȣ��Ǵ� �Լ�
		void Render(HDC hdc);
		void UIClear();				//	UI�� ����� �� ȣ��Ǵ� �Լ�

		void AddChild(UIBase* uiBase);


		eUIType GetType() { return mType; }
		void SetParent(UIBase* parent) { mParent = parent; }

		// �̹��� ���� ������ dx11�� �°� �����ؾ���



	protected:
		virtual void OnInit() {};
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnTick() {};
		virtual void OnRender(HDC hdc) {};
		virtual void OnClear() {};
				
		UIBase* mParent;
		
	protected:
		// �Ƹ��� ������Ʈ�� ������ ������ ������?
		// Tr, Renderer, Script..?

	private:
		std::vector<UIBase*> mChilds;
		eUIType mType;
		bool	mIsEnable;
	};
}