#include "jsMouseScript.h"
#include "jsGameObject.h"
#include "jsTransform.h"
#include "jsInput.h"
#include "jsMeshRenderer.h"
namespace js
{
	MouseScript::MouseScript()
	{
	}
	MouseScript::~MouseScript()
	{
	}
	void MouseScript::Initialize()
	{
	}
	void MouseScript::Update()
	{
		Transform* myTransform = GetOwner()->GetComponent<Transform>();
		Vector3 mousePosition = Input::GetMouseWorldPosition();
		myTransform->SetPosition(mousePosition);
	}
	void MouseScript::FixedUpdate()
	{
	}
	void MouseScript::Render()
	{
	}
}