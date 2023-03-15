#pragma once
#include "jsScript.h"
#include "jsCollider2D.h"

namespace js
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		
		virtual void Start() override;
		virtual void Complete() override;
		virtual void End()override;
		virtual void Action()override;

	private:
		float movespeed;
	};
}
