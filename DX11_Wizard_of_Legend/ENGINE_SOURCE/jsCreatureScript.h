#pragma once
#include "jsScript.h"
#include "jsCollider2D.h"

// ���� ����
#define V2DOWN 0,-1
#define V2RIGHT 1,0
#define V2LEFT -1,0
#define V2UP 0,1

// ���� ����
#define TOP		0
#define BOTTOM	-3.14
#define RIGHT	-1.57
#define LEFT	1.57

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

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void Start() override {};
		virtual void Complete() override {};
		virtual void End()override {};
		virtual void Action()override {};

		// ��� ��ȯ �Լ�
	public:
		Rigidbody* GetRigidbody() { return mRigidbody; }
		Transform* GetTransform() { return mTransform; }
		OffenceStat GetOffenceStat() { return mOffenceStat; }
		HealthStat GetHealthStat() { return mHealthStat; }

		// �ʱ�ȭ ���� �Լ�
	protected:
		// float maxHp, float curHp, float regHp, float moveSpeed
		virtual void initializeHealthStat(float maxHp, float curHp, float regHp,float moveSpeed);
		// float power, float criticalChance, float criticalDamage
		virtual void initializeOffenceStat(float power, float criticalChance, float criticalDamage);
		virtual void createAnimation() {};
		virtual void addEvents() {};

		// �浹 ���� �Լ�
	protected:
		virtual void Hit(CreatureScript* target);
		virtual void knockback(Vector3 dir) {};

		virtual void WallCollision(Script* target);
		virtual void FallCollision(Script* target);






	protected:
		Rigidbody* mRigidbody;
		Transform* mTransform;

		HealthStat mHealthStat;
		OffenceStat mOffenceStat;

	protected:
		Vector2 mAnimationDir;
	};
}