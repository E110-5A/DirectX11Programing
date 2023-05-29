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
		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
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
		bool GetProjectileAbled() { return mProjectileAbled; }

#pragma endregion
		
#pragma region initalize Projectile Info
	protected:
		virtual void createAnimation() {};
		virtual void addEvents() {};
#pragma endregion

#pragma region Collision Object Func
	protected:
		virtual void FindTargetType(Collider2D* collider);
		virtual void CollisionOther(Script* target);

		virtual void CollisionByProjectile(Script* target);
		virtual void CollisionByCreature(Script* target);
		virtual void CollisionByWall(Script* target);
		virtual void CollisionByENV(Script* target);

	public:
		virtual void ProjectileDamaged(float otherProjectile);
		virtual void Disappear();
#pragma endregion

	protected:
		Transform*		mTransform;
		Animator*		mAnimator;
		Collider2D*		mCollider;

	protected:
		Vector2			mAnimationDirection;
		ProjectileStat	mProjectileStat;
	protected:
		bool			mProjectileAbled;		// 투사체 활성화 여부
		bool			mFriendly;				// 투사체가 어디 소속인지 확인용

	private:
		bool			mTesting;
	};
}