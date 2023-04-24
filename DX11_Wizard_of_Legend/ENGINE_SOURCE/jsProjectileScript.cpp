#include "jsProjectileScript.h"
#include "jsObject.h"
namespace js
{
	
	
	
	
	ProjectileScript::ProjectileScript()
		: mRigidbody(nullptr)
		, mTransform(nullptr)
	{
	}
	ProjectileScript::~ProjectileScript()
	{
	}
	void ProjectileScript::Initialize()
	{
		mRigidbody = GetOwner()->GetComponent<Rigidbody>();
		mTransform = GetOwner()->GetComponent<Transform>();
	}
	void ProjectileScript::Update()
	{
	}
	void ProjectileScript::Render()
	{
	}
	void ProjectileScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void ProjectileScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void ProjectileScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void ProjectileScript::Hit(Script* target)
	{
	}
	void ProjectileScript::WallCollision(Script* target)
	{
	}
}