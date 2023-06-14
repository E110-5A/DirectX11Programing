#include "jsItemScript.h"
#include "jsGameObject.h"
#include "jsGameManager.h"
namespace js
{
	ItemScript::ItemScript()
	{
	}
	ItemScript::~ItemScript()
	{
	}
	void ItemScript::Initialize()
	{
		// 컴포넌트 등록
	}
	void ItemScript::Update()
	{
	}
	void ItemScript::Render()
	{
	}
	void ItemScript::OnCollisionEnter(Collider2D* collider)
	{
		eLayerType objectType = collider->GetOwner()->GetLayerType();
		// 충돌대상이 플레이어인 경우
		if (eLayerType::Player == objectType)
		{
			mIsPlayerCollision = true;
		}
	}
	void ItemScript::OnCollisionStay(Collider2D* collider)
	{
		eLayerType objectType = collider->GetOwner()->GetLayerType();
		// 충돌대상이 플레이어인 경우
		if (eLayerType::Player == objectType)
		{
			std::vector<Script*> playerScript = collider->GetOwner()->GetScripts();
			Pickup(playerScript[0]);
		}
	}
	void ItemScript::OnCollisionExit(Collider2D* collider)
	{
		eLayerType objectType = collider->GetOwner()->GetLayerType();
		// 충돌대상이 플레이어인 경우
		if (eLayerType::Player == objectType)
		{
			mIsPlayerCollision = false;
		}
	}
	void ItemScript::Pickup(Script* target)
	{
		
	}
}