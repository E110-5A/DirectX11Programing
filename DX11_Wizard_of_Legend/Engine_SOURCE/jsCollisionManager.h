#pragma once
#include "jsComponent.h"
#include "jsCollider2D.h"

namespace js
{
	union ColliderID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};		
		UINT64 id;
	};

	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void FixedUpdate();
		static void Render();

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable = true);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(Collider2D* left, Collider2D* right);
		static bool Intersect(Collider2D* left, Collider2D* right);

		static bool RectCollision(Collider2D* left, Collider2D* right);
		static bool CircleCollision(Collider2D* left, Collider2D* right);


	public:
		static void CallEnterCollision(Collider2D* left, Collider2D* right, std::map<UINT64, bool>::iterator iter);
		static void CallStayCollision(Collider2D* left, Collider2D* right);
		static void CallExitCollision(Collider2D* left, Collider2D* right, std::map<UINT64, bool>::iterator iter);

	private:
		static std::bitset<(UINT)eLayerType::End> mLayerCollisionMatrix[(UINT)eLayerType::End];
		static std::map<UINT64, bool> mCollisionMap;
	};
}