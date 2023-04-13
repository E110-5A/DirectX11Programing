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

		void CreateAnimation();

		void ActiveProjectile(eArcanaCategory category);
		bool IsReady() { return mIsReady; }
	private:
		void die();
		void shoot();
		void activated();
		void ready();
	private:
		void move();

	private:
		eArcanaCategory mCategory;
		float mLifeTime;
		float mAddTime;
		float mMeleeVelocity;
		float mProjectileSpeed;

		// arcana info | A스킬 B스킬 C스킬 구분.. 할필요가 있나?
		// spell stat | 속도, 거리 공격력, 타입 등
		bool mIsReady;
	};
}