#pragma once
#include "jsBaseRenderer.h"
#include "jsMesh.h"
#include "jsMaterial.h"

// 아직 안쓰는 기능
namespace js
{
	class TileRenderer : public BaseRenderer
	{
	public:
		TileRenderer();
		virtual ~TileRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	private:

	};
}