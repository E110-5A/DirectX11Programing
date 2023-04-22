#pragma once
#include "jsScript.h"

namespace js
{
	class ArcanaScript : public Script
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
		void ActiveArcana(ArcanaInfo& skillInfo);

		eArcanaState GetArcanaState() { return mArcanaState; }

	private:
		void createAnimation();
		void addEvents();
		void bindAnimation();

		void move();

		void endConditionMelee();
		void endConditionProjectile();

	private:
		int mSpellID;
		ArcanaInfo*	mInfo;
		eArcanaState mArcanaState;
		Vector3 mStartPos;
	};
}