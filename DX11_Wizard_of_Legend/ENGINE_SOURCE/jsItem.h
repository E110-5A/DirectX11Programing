#pragma once
#include "jsGameObject.h"
#include "GameObjectComponents.h"
namespace js
{
	class Item : public GameObject
	{
	public:
		Item();
		virtual ~Item();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

	protected:
		// �ִϸ��̼�
		// �浹ü


	private:
	};
}