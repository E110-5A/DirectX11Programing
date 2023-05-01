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
			LBtn,	// 베이직
			RBtn,	// 스탠다드
			Space,	// 대시
			Q,		// 시그니처
			F,		// 스탠다드
			R,		// 스탠다드
			End,
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
		void calculateMouseDirection();
		float calculateRotateAngle();
		int findProjectilePool();
		void projectileRotates(ArcanaScript* target, float angle);

		void playerRush();		// 공격시 약진
		void addForceDash();	// 대시 이동

		// 예정
		void rotatePlayerDirection(float angle);
		void changePlayerDirection(Vector2 direction);
		void changeState(ePlayerState changeState);
		void playAnimation();
		
		// 보류
		void playComboAnimation();
		void playDashMotion();

	private:
		Vector2 mMouseDir;			// 마우스 위치
		Vector2 mPlayerDir;			// 플레이어 위치 (8방향)
		ePlayerState mPlayerState;

		std::vector<ArcanaScript*> mProjectiles;	// 투사체

		// 아르카나, 렐릭이 들어있어요
		Inventory mInventory;

		// 데이터 전달 테스트용
		Arcana mTempArcana;

		Arcana mLBtn;
		Arcana mRBtn;
		Arcana mSpace;
		Arcana mQ;
		Arcana mF;
		Arcana mR;
	};
}