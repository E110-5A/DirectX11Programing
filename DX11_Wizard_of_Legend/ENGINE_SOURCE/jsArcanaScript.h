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
		void SetSpellID(int id) { mSpellID = id; }
		Arcana* GetArcana() { return mArcana; }

	public:
		void ActiveArcana(Arcana* arcana, bool isRight);
		eArcanaState IsActiveProjectile() { return mArcanaState; }

	private:
		void playAnimation();

		void projectileProcess();
		void projectileEndCheck();
		void projectileMove();

		void projectileSleep();

		void disableProjectile();





		void endConditionMelee();
		void endConditionProjectile();

#pragma region legacy
	public:
		void lActiveArcana(lArcanaStat& skillInfo, float power);
		lArcanaStat* GetArcanaInfo() { return mArcanaStat; }

		float GetTotalDamage() { return mArcanaStat->damage * mPower; }
		void lbindAnimation();
		void lmove();
#pragma endregion

	private:
		int mSpellID;
		//ArcanaInfo*	mArcanaInfo;
		eArcanaState mArcanaState;

		float mPower;

	private:
		Arcana* mArcana;
		bool	mIsRight;
	};
}