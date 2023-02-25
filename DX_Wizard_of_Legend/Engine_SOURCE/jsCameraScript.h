#pragma once
#include "jsScript.h"

namespace js
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		virtual ~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}