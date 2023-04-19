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


		void cooldown();
		void skillProcess();
		void shoot(ArcanaInfo& info);

		void calculateMouseDirection();
		float calculateRotateAngle();
		void setPlayerDirection(float angle);
		
		int findProjectilePool();
		void projectileRotates(ArcanaScript* target, float angle);


		void playAnimation(eState changeState);
		void playBasicMotion();
		void playDashMotion();

		void playerRush();	// 공격시 약진
		void addForce();	// 대시 이동

		// 딜레이 초과시 false 반환
		void comboDelayOnCheck();
		bool comboCountOutCheck();
		bool comboValidOutCheck();

		
		void comboReset();

	private:
		Vector2 mMouseDir;
		Vector2 mMoveDir;
		std::vector<ArcanaScript*> mProjectiles;
		// PlayerInfo 사용하기 전 멤버들
		eState mState;
		float mMoveSpeed;

		ArcanaInfo	mAA;
		ArcanaInfo	mSkill;
		ArcanaInfo	mDash;
		ArcanaInfo	mSpecial;
		ArcanaInfo	mUltimate;


		bool mBasicAnimationType;	// 2가지 모션을 번갈아 적용하는 용도




		// 콤보 시작
		bool mComboStarted; // 안씀

		// 콤보 딜레이
		bool mComboDelay;
		// 콤보 진행
		bool mComboProcess;

		// 콤보 횟수
		int mMaxComboCount;
		int mCurComboCount;

		// 콤보 유지 시간
		float mComboValidTime;
		float mComboCurrentValidTime;

		// 콤보 딜레이 시간
		float mComboDelayTime;
		float mComboCurrentDelayTime;
	};
}