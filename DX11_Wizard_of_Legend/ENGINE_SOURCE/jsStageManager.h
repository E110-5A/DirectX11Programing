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
		// Ÿ�� �׷��� �ʿ��ҵ�
		// �Ϻ� ��Ȱ�� ������Ʈ�� ���⿡ ����
	};
}