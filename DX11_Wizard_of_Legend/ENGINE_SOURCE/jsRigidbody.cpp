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
		// ���ӵ� ���ϱ� (A = F / M)
		mAccelation = mForce / mMass;
		// �ӵ� ���ϱ� (A * T * Default)
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
			// ���� ���� ���ϱ� (�ӵ��� �ݴ� ����)
			Vector2 friction = -mVelocity;
			friction.Normalize();

			// ������ ũ��
			friction = friction * mFriction * mMass * Time::DeltaTime();

			// �̵����� �ƴ϶�� ������ ����
			if (mForce == Vector2::Zero)
				friction += friction * 3;

			// �������� �ӵ��� �ѱ��
			if (friction.Length() > mVelocity.Length())
				mVelocity = Vector2::Zero;
			else
				mVelocity += friction;
		}
	}
	void Rigidbody::MoveAction()
	{
		// ���� Position ��������
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
		// �������� ���ϱ�
		Vector2 unitDir = dir;
		unitDir.Normalize();

		// ���� �ӵ��� y���� ���� (�ӵ��� �߷��� �������� ���� : �߷��� �������Ϳ� �����ϱ� ������ �ӵ��� y���и� ����ȴ�)
		float dotDir = unitDir.Dot(velocity);

		// ������ ������ ������ ���������� ���ؼ� �ӵ����� 0���� �����
		mVelocity -= unitDir * dotDir;
	}
	void Rigidbody::EraseVelocity(Vector3 dir, Vector3 velocity)
	{
		// �������� ���ϱ�
		Vector3 unitDir = dir;
		unitDir.z = 1.0f;
		unitDir.Normalize();

		// ���� �ӵ��� y���� ���� (�ӵ��� �߷��� �������� ���� : �߷��� �������Ϳ� �����ϱ� ������ �ӵ��� y���и� ����ȴ�)
		float dotDir = unitDir.Dot(velocity);

		// ������ ������ ������ ���������� ���ؼ� �ӵ����� 0���� �����
		Vector2 eraseVelocity(unitDir.x, unitDir.y);
		mVelocity -= eraseVelocity * dotDir;
	}
	void Rigidbody::EraseVelocity(Vector3 dir, Vector2 velocity)
	{
		// �������� ���ϱ�
		Vector2 unitDir = Vector2(dir.x, dir.y);
		unitDir.Normalize();

		// ���� �ӵ��� y���� ���� (�ӵ��� �߷��� �������� ���� : �߷��� �������Ϳ� �����ϱ� ������ �ӵ��� y���и� ����ȴ�)
		float dotDir = unitDir.Dot(velocity);

		// ������ ������ ������ ���������� ���ؼ� �ӵ����� 0���� �����
		mVelocity -= unitDir * dotDir;
	}
}