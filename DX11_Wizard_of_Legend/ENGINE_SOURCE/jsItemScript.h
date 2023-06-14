#pragma once
#include "jsScript.h"
#include "GameObjectComponents.h"

namespace js
{
	class ItemScript : public Script
	{
	public:
		ItemScript();
		virtual ~ItemScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

	public:
		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void Start() override {};
		virtual void Complete() override {};
		virtual void End()override {};
		virtual void Action()override {};

	public:
		Transform* GetTransform() { return mTransform; }
		Animator* GetAnimator() { return mAnimator; }
		Collider2D* GetCollider() { return mCollider; }

		ProjectileStat GetProjectileStat() { return mProjectileStat; }
		bool GetProjectileAbled() { return mProjectileAbled; }


	protected:
		virtual void createAnimation() {};
		virtual void addEvents() {};

	protected:
		virtual void CollisionPlayer(Script* target);

#pragma endregion

	protected:
		Transform* mTransform;
		Animator* mAnimator;
		Collider2D* mCollider;

	protected:
		bool	mIsPlayerCollision;
	};
}