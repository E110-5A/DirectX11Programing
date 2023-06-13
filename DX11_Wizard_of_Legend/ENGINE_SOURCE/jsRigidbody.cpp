#include "jsRigidbody.h"
#include "jsTime.h"
#include "jsGameObject.h"
#include "jsTransform.h"
namespace js
{
	
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(150.f)
		, mForce(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mAccelation(Vector2::Zero)
	{
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
	}
	void Rigidbody::Update()
	{
		// 가속도 구하기 (A = F / M)
		mAccelation = mForce / mMass;
		// 속도 구하기 (A * T * Default)
		mVelocity += (mAccelation * Time::DeltaTime()) * 300.0f;

		FrictionAction();
		MoveAction();		
	}
	void Rigidbody::FixedUpdate()
	{
	}
	void Rigidbody::Render()
	{
	}
	void Rigidbody::FrictionAction()
	{
		if (!(mVelocity == Vector2::Zero))
		{
			// 마찰 방향 구하기 (속도의 반대 방향)
			Vector2 friction = -mVelocity;
			friction.Normalize();

			// 마찰력 크기
			friction = friction * mFriction * mMass * Time::DeltaTime();

			// 이동중이 아니라면 마찰력 증가
			if (mForce == Vector2::Zero)
				friction += friction * 3;

			// 마찰력이 속도를 넘기면
			if (friction.Length() > mVelocity.Length())
				mVelocity = Vector2::Zero;
			else
				mVelocity += friction;
		}
	}
	void Rigidbody::MoveAction()
	{
		// 오너 Position 가져오기
		Vector3 ownerPosition = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector2 movePosision(ownerPosition.x, ownerPosition.y);
		movePosision += mVelocity * Time::DeltaTime();


		ownerPosition.x = movePosision.x;
		ownerPosition.y = movePosision.y;
		GetOwner()->GetComponent<Transform>()->SetPosition(ownerPosition);
		mForce = Vector2(0.0f, 0.0f);
	}

	void Rigidbody::EraseVelocity(Vector2 dir, Vector2 velocity)
	{
		// 단위벡터 구하기
		Vector2 unitDir = dir;
		unitDir.Normalize();

		// 현재 속도의 y성분 추출 (속도와 중력의 단위벡터 내적 : 중력의 단위벡터와 내적하기 때문에 속도의 y성분만 추출된다)
		float dotDir = unitDir.Dot(velocity);

		// 추출한 벡터의 성분을 역방향으로 더해서 속도값을 0으로 만든다
		mVelocity -= unitDir * dotDir;
	}
	void Rigidbody::EraseVelocity(Vector3 dir, Vector3 velocity)
	{
		// 단위벡터 구하기
		Vector3 unitDir = dir;
		unitDir.z = 1.0f;
		unitDir.Normalize();

		// 현재 속도의 y성분 추출 (속도와 중력의 단위벡터 내적 : 중력의 단위벡터와 내적하기 때문에 속도의 y성분만 추출된다)
		float dotDir = unitDir.Dot(velocity);

		// 추출한 벡터의 성분을 역방향으로 더해서 속도값을 0으로 만든다
		Vector2 eraseVelocity(unitDir.x, unitDir.y);
		mVelocity -= eraseVelocity * dotDir;
	}
	void Rigidbody::EraseVelocity(Vector3 dir, Vector2 velocity)
	{
		// 단위벡터 구하기
		Vector2 unitDir = Vector2(dir.x, dir.y);
		unitDir.Normalize();

		// 현재 속도의 y성분 추출 (속도와 중력의 단위벡터 내적 : 중력의 단위벡터와 내적하기 때문에 속도의 y성분만 추출된다)
		float dotDir = unitDir.Dot(velocity);

		// 추출한 벡터의 성분을 역방향으로 더해서 속도값을 0으로 만든다
		mVelocity -= unitDir * dotDir;
	}
}