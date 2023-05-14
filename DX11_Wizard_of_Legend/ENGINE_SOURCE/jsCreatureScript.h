#pragma once
#include "jsScript.h"
#include "GameObjectComponents.h"

// 벡터 방향
#define V2DOWN 0,-1
#define V2RIGHT 1,0
#define V2LEFT -1,0
#define V2UP 0,1

// 라디안 방향
#define RW		1.57
#define RNW		0.785
#define RN		0
#define RNE		-0.785
#define RE		-1.57
#define RSE		-2.335
#define RS		-3.14
#define RSW		-3.925

#define NORTH		 0
#define SOUTH		-3.14
#define EAST		-1.57
#define WEST		 1.57
namespace js
{
	class CreatureScript : public Script
	{
	public:
		CreatureScript();
		virtual ~CreatureScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

	public:
#pragma region virtual ETC Events
		virtual void OnCollisionEnter(Collider2D* collider) override {};
		virtual void OnCollisionStay(Collider2D* collider) override {};
		virtual void OnCollisionExit(Collider2D* collider) override {};
		virtual void Start() override {};
		virtual void Complete() override {};
		virtual void End()override {};
		virtual void Action()override {};
#pragma endregion

	public:
#pragma region global Member Class & Struct 
		Transform* GetTransform() { return mTransform; }
		Collider2D* GetCollider() { return mCollider; }

		OffenceStat GetOffenceStat() { return mOffenceStat; }
		HealthStat GetHealthStat() { return mHealthStat; }
#pragma endregion

	protected:
#pragma region initalize Creature Info
		// float maxHp, float curHp, float regHp, float moveSpeed
		virtual void initializeHealthStat(float maxHp, float regHp,float moveSpeed, float resistance);
		// float power, float criticalChance, float criticalDamage
		virtual void initializeOffenceStat(float power, float criticalChance, float criticalDamage);
		virtual void createAnimation() {};
		virtual void addEvents() {};
#pragma endregion

	protected:
#pragma region Object State Func
		virtual bool StunStateCheck();

#pragma endregion

	protected:
#pragma region Object Collision Func
		virtual void Hit(ProjectileScript* target);
		virtual void TakeDamage(ProjectileScript* target);
		virtual void Knockback(ProjectileScript* target);

		// 벽이나 낭떠러지? 인 경우 움직임을 막음
		virtual void Blocked(Script* target);
		// 추락함
		virtual void Fall(Script* target);
#pragma endregion

	protected:
		Transform*	mTransform;
		Animator*	mAnimator;
		Collider2D* mCollider;

		HealthStat	mHealthStat;
		OffenceStat mOffenceStat;

	protected:
		Vector2 mAnimationDir;


	protected:
		float mStunTime;
		float mStunCurrentTime;
	};
}