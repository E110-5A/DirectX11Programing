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

/*���� ����ü�� �浹�� exit ȣ���� ���� ����
* ���� ����ü�� ��� ���絵 ��󿡰� Ÿ�� ������ ���� ����
* exit�� ������ �߰� �ؾ��ҵ�
* 
* collisionEnter���� �ε�ģ ����� ��������� ����� ������
* �ִϸ��̼� ������������ exit�� ȣ���ϵ��� �Ѵ�
*/