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
		// ���浹 ��� unit : �ӵ� ���� ����, inner : ���� �ӵ�
		void EraseVelocity(Vector2 dir, Vector2 velocity);
		void EraseVelocity(Vector3 dir, Vector3 velocity);
		void EraseVelocity(Vector3 dir, Vector2 velocity);

	private:
		float	mMass;		// ����
		float	mFriction;	// ������ (����ġ)
		Vector2 mForce;		// �������� ��
		Vector2 mAccelation;// ���ӵ�
		Vector2 mVelocity;	// �ӵ�
	};
}
