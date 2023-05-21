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
		void TurnTest() { mTesting = true; mProjectileAble = true; }
		void Testing();
#pragma endregion

	private:
#pragma region Projectile Process
		void ProjectileProcess();

	public:
#pragma region global Member Class & Struct 
		// component
		Transform* GetTransform() { return mTransform; }
		Animator* GetAnimator() { return mAnimator; }
		Collider2D* GetCollider() { return mCollider; }
		
		// stat & side
		ProjectileStat GetProjectileStat() { return mProjectileStat; }
		void SetProjectileStat(ProjectileStat stat) { mProjectileStat = stat; }
		void PickASide(bool isHostile) { mIsHostile = isHostile; }

		// state
		bool GetProjectileEnable() { return mProjectileAble; }
		void SetProjectileEnable(bool isAble) { mProjectileAble = isAble; }
#pragma endregion
		
	protected:
#pragma region initalize Projectile Info
		virtual void createAnimation() {};
		virtual void addEvents() {};
#pragma endregion

	protected:		
#pragma region Projectile Process
		virtual void ProjectileEndCheck();
#pragma endregion

	protected:
#pragma region Collision Object Func
		virtual void CollisionByProjectile(Script* target);
		virtual void CollisionByCreature(Script* target);
		virtual void CollisionByWall(Script* target);

		virtual void Hit(Script* target);
		virtual void Boom(Script* target);

		virtual void Damaged(float otherProjectile);
	public:
		virtual void Disappear();
#pragma endregion

	protected:
		Transform*		mTransform;
		Animator*		mAnimator;
		Collider2D*		mCollider;

	protected:
		Vector2			mAnimationDirection;
		ProjectileStat	mProjectileStat;
		bool			mProjectileAble;
		bool			mIsHostile;

	private:
		bool			mTesting;
	};
}