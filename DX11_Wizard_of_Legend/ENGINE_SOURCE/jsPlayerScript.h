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
#pragma region State
		void Idle();
		void Move();
		void LBtn();
		void RBtn();
		void Space();
		void Q();
		void F();
		void R();
#pragma endregion

#pragma region Physical Func
		void physicalProcess();
#pragma endregion

#pragma region Skill Func
	private:
		void skillProcess();
		void skillCooldown();
		void skillExcute();
		
		void CooldownCheck(Arcana* target);
		bool delayCheck(Arcana* target);
		bool countCheck(Arcana* target);
		void arcanaCompleteCheck(Arcana* target);
		
		ArcanaScript* redeployProjectiles(Arcana* target);
		void shoot(Arcana* target);
		int findProjectilePool();
		void projectileRotates(ArcanaScript* target, float angle);

		void dashForce();


#pragma endregion

#pragma region Utility Func
	private:
		void	calculateMouseDirection();
		void	calculatePlayerDirection();
		float	calculateRotateAngle();
		void	calculateAnimationDirection(float angle);
#pragma endregion

#pragma region State Func
	private:
		void changePlayerDirection(eAxisValue value, bool isYAxis, bool isKeyUp);
		void changeState(ePlayerState changeState);

		void retIdle() { mPlayerState = ePlayerState::IDLE; playAnimation(); }
#pragma endregion

	private:
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
		eAxisValue	mYDir;
		eAxisValue	mXDir;

	private:
		std::vector<ArcanaScript*> mProjectiles;
		Inventory mInventory;


	private:
		bool		mArcanaUsing;					// 스킬 확인용 변수
		bool		mBasicAnimationType;			// 연계 애니메이션 값
		bool		mIsProjectileRight;				// 투사체 애니메이션 방향값
		float		mArcanaStartAngle;				// 스킬 지정방향 고정값

	private:
		bool		mSprintReady;
		float		mSprintTime;
		float		mSprintCheck;
		float		mSprintSpeed;

	};
}