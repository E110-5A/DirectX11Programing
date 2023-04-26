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

		void SetSpellID(int id) { mSpellID = id; }
		void ActiveArcana(lArcanaStat& skillInfo, float power);

		eArcanaState GetArcanaState() { return mArcanaState; }
		lArcanaStat* GetArcanaInfo() { return mArcanaStat; }

		float GetTotalDamage() { return mArcanaStat->damage * mPower; }

	private:
		void createAnimation();
		void addEvents();
		void bindAnimation();

		void move();

		void endConditionMelee();
		void endConditionProjectile();

	private:
		int mSpellID;
		//ArcanaInfo*	mArcanaInfo;
		eArcanaState mArcanaState;
		Vector3 mStartPos;

		float mPower;
	};
}