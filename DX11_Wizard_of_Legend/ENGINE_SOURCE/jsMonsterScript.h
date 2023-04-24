#pragma once
#include "jsCreatureScript.h"

namespace js
{
	class MonsterScript : public CreatureScript
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Chase,
			Attack1,
			Attack2,
			Attack3,
			Sturn,
			Dead,
			End,
		};

		MonsterScript();
		virtual ~MonsterScript();

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

	protected:
		virtual void createAnimation() override;

		virtual void Hit(Script* target) override;
		virtual void knockback(Vector3 dir) override;
	private:
	};
}