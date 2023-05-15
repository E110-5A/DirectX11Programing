#pragma once

namespace js
{
	class StageManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();
		static void Destroy();
		static void Release();

	private:
		// 타일 그런거 필요할듯
		// 일부 재활용 오브젝트들 여기에 보관
	};
}