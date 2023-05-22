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
		eProjectileState 	IsActiveProjectile() { return mArcanaState; }
		void				SetStartPos(Vector3 ownerPos) { mStartPos = ownerPos; }

	public:
		void ActiveArcana(Arcana* arcana, bool isRight);

	private:
		void playAnimation();

		void projectileProcess();
		void projectileEndCheck();
		void projectileMove();

		void resetProjectile();

		void completedMeleeProjectile();
		void endConditionRangeProjectile();

#pragma region legacy
#pragma endregion

	private:
		int mSpellID;		
		eProjectileState mArcanaState;
		Arcana* mArcana;
		bool	mIsRight;


	private:
		Vector3 mStartPos;
		Collider2D* mTargetCollider;
		float mPower;
	};
}

/*근접 투사체가 충돌후 exit 호출이 되지 않음
* 근접 투사체를 계속 맞춰도 대상에게 타격 판정이 뜨지 않음
* exit를 강제로 뜨게 해야할듯
* 
* collisionEnter에서 부딧친 대상을 멤버변수로 기록한 다음에
* 애니메이션 종료조건으로 exit를 호출하도록 한다
*/