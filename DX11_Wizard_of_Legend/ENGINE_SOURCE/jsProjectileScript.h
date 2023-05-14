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

	public:
#pragma region virtual ETC Events 
		virtual void OnCollisionEnter(Collider2D* collider) override {};
		virtual void OnCollisionStay(Collider2D* collider) override {};
		virtual void OnCollisionExit(Collider2D* collider) override {};
		virtual void Start() override {};
		virtual void Complete() override {};
		virtual void End()override {};
		virtual void Action()override {};
#pragma endregion

#pragma region test Fucn
		void TestAnimation();
		void TurnTest() { mTesting = true; }
		void Testing();
#pragma endregion

	public:
#pragma region global Member Class & Struct 
		Transform* GetTransform() { return mTransform; }
		Animator* GetAnimator() { return mAnimator; }
		Collider2D* GetCollider() { return mCollider; }
		
		ProjectileStat GetProjectileStat() { return mProjectileStat; }
#pragma endregion
		
	protected:
#pragma region initalize Projectile Info
		virtual void createAnimation() {};
		virtual void addEvents() {};
#pragma endregion

	protected:
#pragma region Collision Object Func
		virtual void Hit(Script* target);
		virtual void Disappear(Script* target);
		virtual void Boom(Script* target);
#pragma endregion

	protected:
		Transform*		mTransform;
		Animator*		mAnimator;
		Collider2D*		mCollider;

	protected:
		Vector2			mAnimationDir;
		ProjectileStat	mProjectileStat;
	private:
		bool			mTesting;
	};
}