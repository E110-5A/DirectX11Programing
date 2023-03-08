#pragma once
#include "jsComponent.h"
#include "jsTransform.h"

namespace js
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		virtual ~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 center) { mCenter = center; }

		virtual void OnCollisionEnter(Collider2D* collider);
		virtual void OnCollisionStay(Collider2D* collider);
		virtual void OnCollisionExit(Collider2D* collider);

		virtual void OnTriggerEnter(Collider2D* collider);
		virtual void OnTriggerStay(Collider2D* collider);
		virtual void OnTriggerExit(Collider2D* collider);

		bool IsTrigger() { return mbTrigger; }

		UINT GetID() { return mID; }
		Vector3 GetPosition() { return mPosition; }

	private:
		static UINT ColliderID;
		UINT mID;

	private:
		eColliderType mType;
		Transform* mTransform;

		Vector2 mSize;
		Vector2 mCenter;
		Vector3 mPosition;
		bool mbTrigger;
	};
}