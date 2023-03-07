#pragma once
#include "jsDebugObject.h"
#include "jsEditorObject.h"
#include "jsWidget.h"
#include "jsGraphics.h"

namespace js
{
	class Editor
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();
		virtual void DebugRender(graphics::DebugMesh& mesh);

		virtual void Run();
		virtual void Release();

	private:
		std::vector<Widget*> mWidgets;
		std::vector<EditorObject*> mEditorObjects;
		std::vector<DebugObject*> mDebugObjects;
	};
}