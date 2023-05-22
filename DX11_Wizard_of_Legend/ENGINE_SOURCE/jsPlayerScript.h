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
			LBTN,	// ������
			RBTN,	// ���Ĵٵ�
			SPACE,	// ���
			Q,		// �ñ״�ó
			F,		// ���Ĵٵ�
			R,		// ���Ĵٵ�
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

	private:
#pragma region Skill Func
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

	private:
#pragma region Utility Func
		void	calculateMouseDirection();
		void	calculatePlayerDirection();
		float	calculateRotateAngle();
		void	calculateAnimationDirection(float angle);
#pragma endregion

	private:
#pragma region State Func
		void changePlayerDirection(eAxisValue value, bool isYAxis, bool isKeyUp);
		void changeState(ePlayerState changeState);

		void retIdle() { mPlayerState = ePlayerState::IDLE; playAnimation(); }
#pragma endregion

	private:
#pragma region �ִϸ��̼� �Լ�
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

		// �̵����� ����
		Vector2		mCurrentDirection;
		eAxisValue	mYDir;
		eAxisValue	mXDir;

	private:
		std::vector<ArcanaScript*> mProjectiles;
		Inventory mInventory;

	private:
		bool		mArcanaUsing;
		bool		mBasicAnimationType;
		bool		mIsProjectileRight;
	};
}