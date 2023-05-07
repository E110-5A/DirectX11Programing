#pragma once
#include "jsCreatureScript.h"
#include "jsArcanaScript.h"
namespace js
{
	class PlayerScript : public CreatureScript
	{
	public:
		enum class ePlayerState
		{
			IDLE,
			MOVE,
			LBTN,	// 베이직
			RBTN,	// 스탠다드
			SPACE,	// 대시
			Q,		// 시그니처
			F,		// 스탠다드
			R,		// 스탠다드
			End,
		};
		enum eAxisValue
		{
			Up,
			None,
			Down,
		};

		PlayerScript();
		virtual ~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

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
		
	private:
		void startingArcana();

	public:
		void AddProjectile(ArcanaScript* target) { mProjectiles.push_back(target); }
		void SetProjectileID(int id) { mProjectiles[id]->SetSpellID(id); }
		
	private:
		void Idle();
		void Move();
		void LBtn();
		void RBtn();
		void Space();
		void Q();
		void F();
		void R();

	private:
		void skillProcess();

		void skillCooldown();
		void CooldownCheck(Arcana* target);
		
		void skillExcute();
		bool delayCheck(Arcana* target);
		bool countCheck(Arcana* target);
		void arcanaCompleteCheck(Arcana* target);
		ArcanaScript* redeployProjectiles(Arcana* target);
		void shoot(Arcana* target);

	private:
		void calculateMouseDirection();
		void calculatePlayerDirection();
		float calculateRotateAngle();

		int findProjectilePool();
		void projectileRotates(ArcanaScript* target, float angle);

		void playerRush();
		void addForceDash();
				
		void rotatePlayerDirection(float angle);
		void changePlayerDirection(eAxisValue value, bool isYAxis);
		void changeState(ePlayerState changeState);

	private:
		void retIdle() { mPlayerState = ePlayerState::IDLE; playAnimation(); }

#pragma region 애니메이션 함수
		void playAnimation();		
		void findAnimation(ePlayerMotion motion);
		
		void playIdleAnimation();
		void playMoveAnimation();
		void playBasicAnimation();
		void playGroundSlamAnimation();
		void playAOEAnimation();
		void playKickAnimation();
		void playDashAnimation();
#pragma endregion

	private:
		Vector2 mMouseDir;
		ePlayerState mPlayerState;

		// 이동관련 변수
		Vector2		mCurrentDirection;
		Vector2		mAnimationDirection;
		eAxisValue	mYDir;
		eAxisValue	mXDir;

	private:
		std::vector<ArcanaScript*> mProjectiles;
		Inventory mInventory;

	private:
		bool		mBasicAnimationType;
		bool		mIsProjectileRight;
	};
}