#pragma once
#include "jsComponent.h"
#include "jsScript.h"
#include "jsEntity.h"

namespace js
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			eComponentType order = comp->GetOrder();

			if (order != eComponentType::Script)
			{
				mComponents[(UINT)order] = comp;
				mComponents[(UINT)order]->SetOwner(this);
			}
			else
			{
				mScripts.push_back(dynamic_cast<Script*>(comp));
				comp->SetOwner(this);
			}

			return comp;
		}
		void AddComponent(Component* comp);

		template <typename T>
		T* GetComponent()
		{
			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					return comp;
			}

			return nullptr;
		}
		const std::vector<Script*>& GetScripts() { return mScripts; }
		bool IsDead()
		{
			if (mState == eState::Dead)
				return true;
			
			return false;
		}
		void SetActive() { mState = eState::Active; }
		void Pause() { if (mIsDontChangeState) return; mState = eState::Paused; }
		void Death() { if (mIsDontChangeState) return; mState = eState::Dead; }
		eState GetState() { return mState; }
				
		bool IsDontDestroy() { return mIsDontDestroy; }
		void DontDestroy(bool enable = true) { mIsDontDestroy = enable; }
		bool IsDontChangeState() { return mIsDontChangeState; }
		void DontChangeState(bool enable = true) { mIsDontChangeState = enable; }

		eLayerType GetLayerType() { return mType; }
		void SetLayerType(eLayerType type) { mType = type; }

	protected:
		std::vector<Component*> mComponents;

	private:
		eState mState;
		eLayerType mType;
		std::vector<Script*> mScripts;
		bool mIsDontDestroy;
		bool mIsDontChangeState;
	};
}

