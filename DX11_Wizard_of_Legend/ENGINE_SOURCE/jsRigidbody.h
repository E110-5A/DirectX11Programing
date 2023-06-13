#pragma once
#include "jsComponent.h"

namespace js
{
	using namespace math;
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void FrictionAction();
		void MoveAction();

	public:
		void AddForce(Vector2 force) { mForce += force; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

	public:
		// 벽충돌 기능 unit : 속도 통제 방향, inner : 현재 속도
		void EraseVelocity(Vector2 dir, Vector2 velocity);
		void EraseVelocity(Vector3 dir, Vector3 velocity);
		void EraseVelocity(Vector3 dir, Vector2 velocity);

	private:
		float	mMass;		// 질량
		float	mFriction;	// 마찰력 (감속치)
		Vector2 mForce;		// 가해지는 힘
		Vector2 mAccelation;// 가속도
		Vector2 mVelocity;	// 속도
	};
}
