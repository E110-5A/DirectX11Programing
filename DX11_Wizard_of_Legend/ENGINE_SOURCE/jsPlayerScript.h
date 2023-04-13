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

		enum class eArcanaType
		{
			AA,
			Skill,
			Dash,
			Special,
			Ultimate,
			End,
		};

		enum class eStagger
		{
			Light,
			Normal,
			Heave,
		};

		struct ArcanaInfo
		{
			// 피해량 = 채력
			float power;
			// 카테고리
			eArcanaCategory category;
			// 재사용 대기시간
			float cooldown;
			// 재사용 대기시간2
			float colldownDT;
			// 스테거
			eStagger stagger;
		};

		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetProjectile(ArcanaScript* target) { mProjectile = target; }
		void AddProjectile(ArcanaScript* target) { mProjectiles.push_back(target); }

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
		void idleState();
		void shoot();
		void calculateMouseDir();
		float calculateRotate();
		
		void projectileRotate(float angle);
		void activeProjectile();

		void playerRotate(float angle);
		void playerRush();

		void projectileRotates(ArcanaScript* target, float angle);
		void activeProjectiles(ArcanaScript* target);
	private:
		Vector2 mMoveDir;
		Vector2 mMouseDir;
		eState mState;
		float mMoveSpeed;
		ArcanaScript* mProjectile;
		std::vector<ArcanaScript*> mProjectiles;

		eArcanaCategory mProjectileType;
		ArcanaInfo mArcanaInfo;
	};
}