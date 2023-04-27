#pragma once
#include "jsCreatureScript.h"
#include "jsArcanaScript.h"
namespace js
{
	class PlayerScript : public CreatureScript
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
		enum class ePlayerState
		{
			Idle,
			Move,
			LBtn,	// ������
			RBtn,	// ���Ĵٵ�
			Space,	// ���
			Q,		// �ñ״�ó
			F,		// ���Ĵٵ�
			R,		// ���Ĵٵ�
			End,
		};
		
		PlayerScript();
		virtual ~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;
				
		void AddProjectile(ArcanaScript* target) { mProjectiles.push_back(target); }
		void SetProjectileID(int id) { mProjectiles[id]->SetSpellID(id); }

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void Start() override;
		virtual void Complete() override;
		virtual void End()override;
		virtual void Action()override;
			
	protected:
		virtual void createAnimation()override;
		virtual void addEvents()override;
		
	public:
		PlayerInfo GetPlayerInfo() { return mInfo; }
		

	private:

		void initializeArcana(lArcanaInfo& skill, elArcanaCategory category, elArcanaType arcanaType, elStagger stagger
			, float damage, float moveSpeed, float spellRange, float cooldown
			, int mMaxComboCount, float mComboValidTime, float mComboDelayTime);

		void Idle();
		void Move();
		void LBtn();
		void RBtn();
		void Space();
		void Q();
		void F();
		void R();

		void setIdle() { playAnimation(eState::Idle); }
		void setMove() { mState = eState::Move; }


	private:
		void calculateMouseDirection();
		float calculateRotateAngle();
		void setPlayerDirection(float angle);

		int findProjectilePool();
		void projectileRotates(ArcanaScript* target, float angle);


		void playAnimation(eState changeState);
		void playBasicMotion();
		void playDashMotion();

		void playerRush();	// ���ݽ� ����
		void addForce();	// ��� �̵�
		
		
		
		// ���Ž�
		void AA();
		void Skill();
		void Dash();
		void Special();
		void Ultimate();
		void setAA() { mState = eState::AA; }
		void setSkill() { mState = eState::Skill; }
		void setDash() { mState = eState::Dash; }
		void setSpecial() { mState = eState::Special; }
		void setUltimate() { mState = eState::Ultimate; }

		void cooldown();
		void comboCooldown(lArcanaInfo& info);
		void skillProcess();
		void shoot(lArcanaInfo& info);

		

		// ������ �ʰ��� false ��ȯ
		bool comboCountOutCheck(lArcanaInfo& info);
		bool comboValidOutCheck(lArcanaInfo& info);

		
		void comboReset(lArcanaInfo& info);

	private:
		Vector2 mMoveDir;		// 8����
		Vector2 mMouseDir;
		std::vector<ArcanaScript*> mProjectiles;
		ePlayerState mPlayerState;

		// �Ƹ�ī��, ������ ����־��
		Inventory mInventory;



		// ���Ž�
		eState mState;
		PlayerInfo mInfo;

		lArcanaInfo	mAA;
		lArcanaInfo	mSkill;
		lArcanaInfo	mDash;
		lArcanaInfo	mSpecial;
		lArcanaInfo	mUltimate;
		bool mBasicAnimationType;	// 2���� ����� ������ �����ϴ� �뵵
	};
}