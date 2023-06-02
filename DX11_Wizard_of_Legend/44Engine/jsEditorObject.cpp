#include "jsEditorObject.h"

namespace js
{
	EditorObject::EditorObject()
		: GameObject()
	{
		GameObject::Initialize();
	}
	EditorObject::~EditorObject()
	{

	}
	void EditorObject::Initialize()
	{
		GameObject::Initialize();
	}
	void EditorObject::Update()
	{
		GameObject::Update();
	}
	void EditorObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void EditorObject::Render()
	{
		GameObject::Render();
	}
}