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

		void playerRush();		// ���ݽ� ����
		void addForceDash();	// ��� �̵�

		// ����
		void rotatePlayerDirection(float angle);
		void changePlayerDirection(Vector2 direction);
		void changeState(ePlayerState changeState);
		void playAnimation();
		
		// ����
		void playComboAnimation();
		void playDashMotion();

	private:
		Vector2 mMouseDir;			// ���콺 ��ġ
		Vector2 mPlayerDir;			// �÷��̾� ��ġ (8����)
		ePlayerState mPlayerState;

		std::vector<ArcanaScript*> mProjectiles;	// ����ü

		// �Ƹ�ī��, ������ ����־��
		Inventory mInventory;

		// ������ ���� �׽�Ʈ��
		Arcana mTempArcana;

		Arcana mLBtn;
		Arcana mRBtn;
		Arcana mSpace;
		Arcana mQ;
		Arcana mF;
		Arcana mR;
	};
}