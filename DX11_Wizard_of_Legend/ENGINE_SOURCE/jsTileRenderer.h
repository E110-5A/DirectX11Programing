#pragma once
#include "jsBaseRenderer.h"
#include "jsMesh.h"
#include "jsMaterial.h"
#include "TileStruct.h"

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

		void SetTileInfo(Vector2 leftTop, Vector2 tileSize, Vector2 tilesetSize) 
		{ 
			mTileInfo.leftTop = leftTop; 
			mTileInfo.tileSize = tileSize;
			mTileInfo.tilesetSize = tilesetSize;
		}
		void SetTileInfo(TileSet& info) { mTileInfo = info; }
		void SetTileSet(std::shared_ptr<Texture> texture) { mAtlas = texture; }

	public:
		void Clear();
		void BindShader();

	private:
		std::shared_ptr<Texture>	mAtlas;
		TileSet						mTileInfo;
	};
}