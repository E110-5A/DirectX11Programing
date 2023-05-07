#pragma once
#include "jsScript.h"
#include "GameObjectComponents.h"

namespace js
{
	class ProjectileScript : public Script
	{
	public:
		ProjectileScript();
		virtual ~ProjectileScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void Start() override {};
		virtual void Complete() override {};
		virtual void End()override {};
		virtual void Action()override {};

		// 멤버 반환 함수
	public:
		Rigidbody* GetRigidbody() { return mRigidbody; }
		Transform* GetTransform() { return mTransform; }

		// 초기화 관련 함수
	protected:
		virtual void createAnimation() {};
		virtual void addEvents() {};
		

		// 충돌 관련 함수
	protected:
		virtual void Hit(Script* target);
		virtual void WallCollision(Script* target);

	protected:
		Transform*		mTransform;
		Rigidbody*		mRigidbody;
		Animator*		mAnimator;


		lArcanaStat*	mArcanaStat;
	protected:
		Vector2			mAnimationDir;
	};
}