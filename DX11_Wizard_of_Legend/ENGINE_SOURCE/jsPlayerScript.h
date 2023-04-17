#pragma once
#include "jsScript.h"
#include "jsCollider2D.h"
#include "jsArcanaScript.h"
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

		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
				
		void AddProjectile(ArcanaScript* target) { mProjectiles.push_back(target); }

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void Start() override;
		virtual void Complete() override;
		virtual void End()override;
		virtual void Action()override;

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
		void initializeArcana(ArcanaInfo& skill, eArcanaCategory category, eArcanaType arcanaType, eStagger stagger, float damage, float range, int count, float cooldown);

		void setIdle() { playAnimation(eState::Idle); }
		void setMove() { mState = eState::Move; }
		void setAA() { mState = eState::AA; }
		void setSkill() { mState = eState::Skill; }
		void setDash() { mState = eState::Dash; }
		void setSpecial() { mState = eState::Special; }
		void setUltimate() { mState = eState::Ultimate; }

		void playAnimation(eState changeState);

		void cooldown();
		void skillProcess();



		void shoot(ArcanaInfo& info);
		void calculateMouseDir();
		float calculateRotate();
		
		int findProjectilePool();

		void setPlayerDirection(float angle);
		void playerRush();

		void projectileRotates(ArcanaScript* target, float angle);
		void activeProjectiles(ArcanaScript* target);


		void setStateDash();
		void retIdle();		// 이건 사용하는거
		void addForce();	// 대시에 사용함


	private:
		Vector2 mMoveDir;
		Vector2 mMouseDir;
		eState mState;
		float mMoveSpeed;
		std::vector<ArcanaScript*> mProjectiles;

		ArcanaInfo	mAA;
		ArcanaInfo	mSkill;
		ArcanaInfo	mDash;
		ArcanaInfo	mSpecial;
		ArcanaInfo	mUltimate;

		int mComboCount;
		int mCurrentCount;
		float mComboValidTime;
		float mComboCurrentTime;

		// 안씀
		eArcanaCategory mProjectileType;
		ArcanaScript* mProjectile;
	};
}