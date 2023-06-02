#pragma once
#include "jsProjectileScript.h"

namespace js
{
	class ArcanaScript : public ProjectileScript
	{
	public:
		ArcanaScript();
		virtual ~ArcanaScript();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		virtual void OnTriggerEnter(Collider2D* collider) override;
		virtual void OnTriggerStay(Collider2D* collider) override;
		virtual void OnTriggerExit(Collider2D* collider) override;

		virtual void Start() override;
		virtual void Complete() override;
		virtual void End() override;
		virtual void Action() override;

	protected:
		virtual void createAnimation() override;
		virtual void addEvents() override;

	public:
		void				SetSpellID(int id) { mSpellID = id; }
		void				SetStartPos(Vector3 ownerPos) { mStartPos = ownerPos; }

#pragma region Player Call
	public:
		void ActiveArcana(Arcana* arcana, bool isRight);
	private:
		void playAnimation();
#pragma endregion
	private:
		void projectileProcess();
		void projectileEndCheck();
		void projectileMove();

		void resetProjectile();

		void endConditionRangeProjectile();

#pragma region Collision Func
		virtual void CollisionByProjectile(Script* target) override;
		virtual void CollisionByCreature(Script* target) override;

#pragma endregion

	private:
		int mSpellID;		
		Arcana* mArcana;
		bool	mIsRight;

	private:
		Vector3 mStartPos;
		float mPower;

		float mRotateValue;
	};
}