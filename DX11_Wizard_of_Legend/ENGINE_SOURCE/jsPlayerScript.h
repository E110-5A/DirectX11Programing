#pragma once
#include "jsScript.h"
#include "jsCollider2D.h"

namespace js
{
	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			AA,
			Skill,
			Dash,
			Special,
			Ultimate,
			End,
		};

		enum class eArcanaType
		{
			AA,
			Skill,
			Dash,
			Special,
			Ultimate,
			End,
		};

		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetProjectile(ArcanaScript* target) { mProjectile = target; }

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void Start() override;
		virtual void Complete() override;
		virtual void End()override;
		virtual void Action()override;


	public:
		void RetIdle();
		void AddForce();
		void AutoAttack();

	public:
		void Idle();
		void Move();
		void AA();
		void Skill();
		void Dash();
		void Special();
		void Ultimate();

	private:
		void createAnimation();
		void addEvent();
		void dashAction();
		void shoot();
		void calculateProjectileDir();
		void activeProjectile();
		void idleState();

	private:
		Vector2 mMoveDir;
		eState mState;
		float mMoveSpeed;
		//GameObject* mProjectile;
		class ArcanaScript* mProjectile;
	};
}