#pragma once
#include "jsScript.h"

namespace js
{
	class ENVScript : public Script
	{
	public:
		ENVScript();
		virtual ~ENVScript();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider2D* collider) {};
		virtual void OnCollisionStay(Collider2D* collider) {};
		virtual void OnCollisionExit(Collider2D* collider) {};

		virtual void OnTriggerEnter(Collider2D* collider) {};
		virtual void OnTriggerStay(Collider2D* collider) {};
		virtual void OnTriggerExit(Collider2D* collider) {};

		virtual void Start() {};
		virtual void Complete() {};
		virtual void End() {};
		virtual void Action() {};
	public:
		void DestroyObj() {};

		// 아마 이미지 정보를 가지고 있을려나?

	};
}