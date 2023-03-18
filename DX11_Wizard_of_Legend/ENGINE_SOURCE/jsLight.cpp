#include "jsLight.h"
#include "jsGameObject.h"
#include "jsTransform.h"
#include "jsRenderer.h"

namespace js
{
	Light::Light()
		: Component(eComponentType::Light)
	{
	}
	Light::~Light()
	{
	}
	void Light::Initialize()
	{
	}
	void Light::Update()
	{
	}
	void Light::FixedUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 position = tr->GetPosition();
		mAttribute.posision = Vector4(position.x, position.y, position.z, 1.0f);
		mAttribute.direction = Vector4(tr->Right().x, tr->Right().y, tr->Right().z, 1.0f);

		// Light 컴포넌트 정보를 전역변수에 push_back
		renderer::PushLightAttribute(mAttribute);
	}
	void Light::Render()
	{
	}
}