#pragma once
#include "jsComponent.h"
#include "jsScript.h"
#include "jsEntity.h"
#include "jsTransform.h"
namespace js
{
	class GameObject : public Entity
	{
	public:
		enum eGlobalState
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
			comp->Initialize();
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

		template <typename T>
		std::vector<T*> GetComponents()
		{
			std::vector<T*> components = {};

			T* comp;
			for (auto c : mComponents)
			{
				comp = dynamic_cast<T*>(c);

				if (comp != nullptr)
					components.push_back(comp);
			}

			return components;
		}

		const std::vector<Script*>& GetScripts() { return mScripts; }
		bool IsDead()
		{
			if (mState == eGlobalState::Dead)
				return true;
			
			return false;
		}

		void OnActive() { mState = eGlobalState::Active; }
		void OnPause() { if (mIsDontChangeState) return; mState = eGlobalState::Paused; }
		void OnDeath() { if (mIsDontChangeState) return; mState = eGlobalState::Dead; }
		eGlobalState GetState() { return mState; }
		
		bool IsDontDestroy() { return mIsDontDestroy; }
		void DontDestroy(bool enable = true) { mIsDontDestroy = enable; }
		bool IsDontChangeState() { return mIsDontChangeState; }
		void DontChangeState(bool enable = true) { mIsDontChangeState = enable; }

		eLayerType GetLayerType() { return mType; }
		void SetLayerType(eLayerType type) { mType = type; }

	protected:
		std::vector<Component*> mComponents;
		Transform* mTransform;

	private:
		eGlobalState mState;
		eLayerType mType;
		std::vector<Script*> mScripts;
		bool mIsDontDestroy;
		bool mIsDontChangeState;
	};
}

