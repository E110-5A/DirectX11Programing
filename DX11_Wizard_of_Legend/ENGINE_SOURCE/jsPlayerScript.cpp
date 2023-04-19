#include "jsPlayerScript.h"

#include "jsInput.h"
#include "jsTime.h"

#include "jsResources.h"

#include "jsGameObject.h"

#include "jsTransform.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"
#include "jsArcanaScript.h"


// ���� ����
#define V2DOWN 0,-1
#define V2RIGHT 1,0
#define V2LEFT -1,0
#define V2UP 0,1

// ���� ����
#define TOP		0
#define BOTTOM	-3.14
#define RIGHT	-1.57
#define LEFT	1.57

namespace js
{
	PlayerScript::PlayerScript()
		: Script()
		, mState(eState::Idle)
		, mMoveSpeed(3.0f)
		, mMoveDir(Vector2(V2DOWN))
		, mMouseDir(Vector2::Zero)
		, mProjectiles{}, mAA{}, mSkill{}, mDash{}, mSpecial{}, mUltimate{}
		, mBasicAnimationType(true)
		, mComboStarted(false)
		, mComboDelay(false)
		, mComboProcess(false)
		, mMaxComboCount(4)
		, mCurComboCount(0)
		, mComboValidTime(0.9)
		, mComboCurrentValidTime(0.0f)
		, mComboDelayTime(0.4f)
		, mComboCurrentDelayTime(0.0f)
	{
	}
	

	
	
	
	
	PlayerScript::~PlayerScript()
	{
	}

#pragma region �ʱ�ȭ
	void PlayerScript::Initialize()
	{
		createAnimation();
		addEvent();
		// ��� �����ϱ�
		// �ٰŸ� ��Ÿ (�޺� ��� ������!)
		initializeArcana(mAA, eArcanaCategory::Melee, eArcanaType::AA, eStagger::Light, 6.0f, 30.0f, 1, 1.4f);		
		// Dragon_Arc
		initializeArcana(mSkill, eArcanaCategory::Projectile, eArcanaType::Skill, eStagger::Normal, 6.5f, 20.0f, 1, 3.0f);
		// ����� 
		initializeArcana(mDash, eArcanaCategory::Melee, eArcanaType::Dash, eStagger::Light, 3.0f, 60.0f, 1, 1.0f);
		// ��ä�÷� ���� ����ü?
		initializeArcana(mSpecial, eArcanaCategory::Projectile, eArcanaType::Special, eStagger::Normal, 6.5f, 20.0f, 1, 4.0f);
		// Shearing_Chain �ٰŸ� ��â
		initializeArcana(mUltimate, eArcanaCategory::Melee, eArcanaType::Ultimate, eStagger::Heave, 6.5f, 20.0f, 1, 4.0f);
	}
	
	void PlayerScript::createAnimation()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Vector2 defaultSize = Vector2(48.0f, 48.0f);
		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"PlayerSpriteSheet", L"Player\\PlayerSpriteSheet.png");
		// Idle
		{
			animator->Create(L"PlayerIdleDown", texture, Vector2(0.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerIdleRight", texture, Vector2(48.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerIdleLeft", texture, Vector2(96.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerIdleUp", texture, Vector2(144.0f, 0.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		}
		// Move
		{
			animator->Create(L"PlayerRunDown",	texture, Vector2(0.0f, 49.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunRight", texture, Vector2(0.0f, 97.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunLeft",	texture, Vector2(0.0f, 145.0f), defaultSize, Vector2::Zero, 10, 0.08f);
			animator->Create(L"PlayerRunUp",	texture, Vector2(0.0f, 193.0f), defaultSize, Vector2::Zero, 10, 0.08f);
		}
		// Hurt
		{
			animator->Create(L"PlayerHurtDown", texture, Vector2(0.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerHurtRight", texture, Vector2(48.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerHurtLeft", texture, Vector2(96.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
			animator->Create(L"PlayerHurtUp", texture, Vector2(144.0f, 1111.0f), defaultSize, Vector2::Zero, 1, 0.1f);
		}
		
		// Dash
		{
			animator->Create(L"PlayerDashDown", texture, Vector2(0.0f, 242.0f),		defaultSize, Vector2::Zero, 4, 0.1f);
			animator->Create(L"PlayerDashRight", texture, Vector2(0.0f, 290.0f),	defaultSize, Vector2::Zero, 6, 0.1f);
			animator->Create(L"PlayerDashLeft", texture, Vector2(0.0f, 338.0f),		defaultSize, Vector2::Zero, 6, 0.1f);
			animator->Create(L"PlayerDashUp", texture, Vector2(0.0f, 386.0f),		defaultSize, Vector2::Zero, 5, 0.1f);
		}
		// Basic
		{
			animator->Create(L"PlayerBackhandDown", texture, Vector2(0.0f, 435.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandRight", texture, Vector2(0.0f, 483.0f),	defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandLeft", texture, Vector2(0.0f, 531.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerBackhandUp", texture, Vector2(0.0f, 579.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerForehandDown", texture, Vector2(0.0f, 628.0f),		defaultSize, Vector2::Zero, 9,  0.04f);
			animator->Create(L"PlayerForehandRight", texture, Vector2(0.0f, 676.0f),	defaultSize, Vector2::Zero, 8,  0.04f);
			animator->Create(L"PlayerForehandLeft", texture, Vector2(0.0f, 724.0f),		defaultSize, Vector2::Zero, 8,  0.04f);
			animator->Create(L"PlayerForehandUp", texture, Vector2(0.0f, 772.0f),		defaultSize, Vector2::Zero, 12, 0.04f);
		}
		// Slam
		{
			animator->Create(L"PlayerGroundSlamDown", texture, Vector2(0.0f, 821.0f), defaultSize, Vector2::Zero, 10, 0.1f);
			animator->Create(L"PlayerGroundSlamUp", texture, Vector2(0.0f, 869.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		}
		// AOE
		{
			animator->Create(L"PlayerAOEDown", texture, Vector2(0.0f, 918.0f),	defaultSize, Vector2::Zero, 9, 0.085f);
			animator->Create(L"PlayerAOERight", texture, Vector2(0.0f, 966.0f), defaultSize, Vector2::Zero, 12, 0.07f);
			animator->Create(L"PlayerAOELeft", texture, Vector2(0.0f, 1014.0f), defaultSize, Vector2::Zero, 12, 0.07f);
			animator->Create(L"PlayerAOEUp", texture, Vector2(0.0f, 1062.0f),	defaultSize, Vector2::Zero, 11, 0.07f);
		}
		// Kick
		{
			animator->Create(L"PlayerKickDown", texture, Vector2(0.0f, 1159.0f),	defaultSize, Vector2::Zero, 11, 0.06f);
			animator->Create(L"PlayerKickLeft", texture, Vector2(0.0f, 1255.0f),	defaultSize, Vector2::Zero, 9, 0.07f);
			animator->Create(L"PlayerKickRight", texture, Vector2(0.0f, 1207.0f),	defaultSize, Vector2::Zero, 9, 0.07f);
			animator->Create(L"PlayerKickUp", texture, Vector2(0.0f, 1303.0f),		defaultSize, Vector2::Zero, 8, 0.07f);
		}

		animator->Play(L"PlayerIdleDown");
	}
	void PlayerScript::addEvent()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// ����
		{
		//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		//animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		//animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		//animator->GetActionEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
		}
		// Dash (setIdle, addForce)
		{
			animator->GetActionEvent(L"PlayerDashDown", 3) = std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerDashRight", 3) = std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerDashLeft", 3) = std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerDashUp", 3) = std::bind(&PlayerScript::setIdle, this);
			animator->GetStartEvent(L"PlayerDashDown") = std::bind(&PlayerScript::addForce, this);
			animator->GetStartEvent(L"PlayerDashRight") = std::bind(&PlayerScript::addForce, this);
			animator->GetStartEvent(L"PlayerDashLeft") = std::bind(&PlayerScript::addForce, this);
			animator->GetStartEvent(L"PlayerDashUp") = std::bind(&PlayerScript::addForce, this);
		}
		// Basic (setIdle, playerRush)
		{
			animator->GetCompleteEvent(L"PlayerBackhandDown")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandRight")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandLeft")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandUp")		= std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerBackhandDown", 3)	= std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandRight", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandLeft", 3)	= std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandUp", 3)	= std::bind(&PlayerScript::playerRush, this);

			animator->GetCompleteEvent(L"PlayerForehandDown")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandRight")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandLeft")	= std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandUp")		= std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerForehandDown", 3)	= std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandRight", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandLeft", 3)	= std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandUp", 3)	= std::bind(&PlayerScript::playerRush, this);

		}
		// GroundSlam (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerGroundSlamDown") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerGroundSlamUp") = std::bind(&PlayerScript::setIdle, this);
		}
		// AOE (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerAOEDown") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerAOERight") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerAOELeft") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerAOEUp") = std::bind(&PlayerScript::setIdle, this);
		}
		// Kick (setIdle)
		{
			animator->GetCompleteEvent(L"PlayerKickDown") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerKickLeft") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerKickRight") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerKickUp") = std::bind(&PlayerScript::setIdle, this);
		}
	}
	void PlayerScript::initializeArcana(ArcanaInfo& skill, eArcanaCategory category, eArcanaType arcanaType, eStagger stagger, float damage, float range, int count, float cooldown)
	{
		skill.category = category;
		skill.arcanaType = arcanaType;
		skill.stagger = stagger;
		skill.damage = damage;
		skill.range = range;
		skill.maxCount = count;
		skill.curCount = 0;
		skill.cooldownTime = cooldown;
		skill.currentTime = 0.0f;
		skill.cooldownReady = true;
	}
#pragma endregion

	void PlayerScript::Update()
	{
		// ��ٿ�
		cooldown();
		// �� ���º� �ൿ (�ִϸ��̼� ����)
		switch (mState)
		{
		case eState::Idle:
		{
			Idle();
		}
		break;
		case eState::Move:
		{
			Move();
		}
		break;
		case eState::Dash:
		{
			Dash();
		}
		break;
		case eState::AA:
		{
			AA();
		}
		break;
		case eState::Skill:
		{
			Skill();
		}
		break;
		case eState::Special:
		{
			Special();
		}
		break;
		case eState::Ultimate:
		{
			Ultimate();
		}
		break;
		}

		// ��ų ����?
		skillProcess();

		calculateMouseDirection();

		// �׽�Ʈ (KEY : K, L)
		{
			if (Input::GetKey(eKeyCode::K))
			{
				GetOwner()->Kill();
			}
			if (Input::GetKey(eKeyCode::L))
			{
				GetOwner()->Alive();
			}
		}
	}

	void PlayerScript::Render()
	{
	}

#pragma region �浹 �� �̺�Ʈ
	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void PlayerScript::Start()
	{
	}
	void PlayerScript::Complete()
	{
	}
	void PlayerScript::End()
	{
	}
	void PlayerScript::Action()
	{
	}
#pragma endregion 


	void PlayerScript::Idle()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// �ִϸ��̼�
		if (Input::GetKey(eKeyCode::S))
		{
			animator->Play(L"PlayerRunDown");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::D))
		{
			animator->Play(L"PlayerRunRight");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::A))
		{
			animator->Play(L"PlayerRunLeft");
			mState = eState::Move;
		}
		if (Input::GetKey(eKeyCode::W))
		{
			animator->Play(L"PlayerRunUp");
			mState = eState::Move;
		}

		if (Input::GetKey(eKeyCode::LBTN) && true == mAA.cooldownReady)
		{
			playAnimation(eState::AA);
		}
		if (Input::GetKey(eKeyCode::RBTN) && true == mSkill.cooldownReady)
		{
			playAnimation(eState::Skill);
		}
		if (Input::GetKey(eKeyCode::SPACE) && true == mDash.cooldownReady)
		{
			playDashMotion();
		}
		if (Input::GetKey(eKeyCode::F) && true == mSpecial.cooldownReady)
		{
			playAnimation(eState::Special);
		}
		if (Input::GetKey(eKeyCode::Q) && true == mUltimate.cooldownReady)
		{
			playAnimation(eState::Ultimate);
		}

	}
	void PlayerScript::Move()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();
		// �̵� ����
		if (Input::GetKey(eKeyCode::S))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Up() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(V2DOWN);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Right() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(V2RIGHT);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Right() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(V2LEFT);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Up() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(V2UP);
		}

		// �ִϸ��̼�
		if (Input::GetKey(eKeyCode::LBTN) && true == mAA.cooldownReady)
		{
			playAnimation(eState::AA);
		}
		if (Input::GetKey(eKeyCode::RBTN) && true == mSkill.cooldownReady)
		{
			playAnimation(eState::Skill);
		}
		if (Input::GetKey(eKeyCode::SPACE) && true == mDash.cooldownReady)
		{
			playDashMotion();
		}
		if (Input::GetKey(eKeyCode::F) && true == mSpecial.cooldownReady)
		{
			playAnimation(eState::Special);
		}
		if (Input::GetKey(eKeyCode::Q) && true == mUltimate.cooldownReady)
		{
			playAnimation(eState::Ultimate);
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			animator->Play(L"PlayerIdleDown");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			animator->Play(L"PlayerIdleRight");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			animator->Play(L"PlayerIdleLeft");
			mState = eState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::W))
		{
			animator->Play(L"PlayerIdleUp");
			mState = eState::Idle;
		}

	}
	void PlayerScript::AA()
	{
		// �ִϸ��̼�
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}

		// ����
		if (Input::GetKey(eKeyCode::LBTN))
		{
			// ��� ���°� �ƴ϶��
			if (false == mComboDelay)
			{
				mComboProcess = true;
			}
		}
	}
	void PlayerScript::Skill()
	{
		// �ִϸ��̼�
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
		
		// ����

	}
	void PlayerScript::Dash()
	{
		// ����

	}
	void PlayerScript::Special()
	{
		// �ִϸ��̼�
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
		// ����

	}
	void PlayerScript::Ultimate()
	{
		// �ִϸ��̼�
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}

		// ����

	}

	void PlayerScript::cooldown()
	{
		// �޺�
		if (true == mComboDelay)
			mComboCurrentDelayTime += Time::DeltaTime();
		if (true == mComboProcess)
			mComboCurrentValidTime += Time::DeltaTime();

		if (mComboCurrentDelayTime >= mComboDelayTime)
		{
			mComboDelay = false;
			mComboCurrentDelayTime = 0.0f;
		}

		// LBTN
		if (false == mAA.cooldownReady)
		{
			mAA.currentTime += Time::DeltaTime();

			if (mAA.currentTime >= mAA.cooldownTime)
			{
				mAA.cooldownReady = true;
				mAA.currentTime = 0.0f;
			}
		}
		// RBTN
		if (false == mSkill.cooldownReady)
		{
			mSkill.currentTime += Time::DeltaTime();

			if (mSkill.currentTime >= mSkill.cooldownTime)
			{
				mSkill.cooldownReady = true;
				mSkill.currentTime = 0.0f;
			}
		}		
		// SPACE
		if (false == mDash.cooldownReady)
		{
			mDash.currentTime += Time::DeltaTime();

			if (mDash.currentTime >= mDash.cooldownTime)
			{
				mDash.cooldownReady = true;
				mDash.currentTime = 0.0f;
			}
		}
		// F
		if (false == mSpecial.cooldownReady)
		{
			mSpecial.currentTime += Time::DeltaTime();

			if (mSpecial.currentTime >= mSpecial.cooldownTime)
			{
				mSpecial.cooldownReady = true;
				mSpecial.currentTime = 0.0f;
			}
		}
		// Q
		if (false == mUltimate.cooldownReady)
		{
			mUltimate.currentTime += Time::DeltaTime();

			if (mUltimate.currentTime >= mUltimate.cooldownTime)
			{
				mUltimate.cooldownReady = true;
				mUltimate.currentTime = 0.0f;
			}
		}
	}
	void PlayerScript::skillProcess()
	{		
		if (true == mAA.cooldownReady)
		{
			if (true == mComboProcess)
			{
				// �޺� ī��Ʈ �Ѱ���� Ȯ��
				if (comboCountOutCheck())
					return;
				// �޺� ��ȿ�ð� �Ѱ���� Ȯ��
				if (comboValidOutCheck())
					return;

				// ���������� ��Ÿ ����!
				if (false == mComboDelay)
				{
					++mCurComboCount;
					mComboDelay = true;
				}
				//shoot();
			}
		}
		

		switch (mState)
		{
		case js::PlayerScript::eState::AA:
		{

			//// ��ٿ� �׽�Ʈ
			//if (true == mAA.cooldownReady)
			//{
			//	mAA.cooldownReady = false;
			//}
		}
		break;
		case js::PlayerScript::eState::Skill:
		{			
			// ��ٿ� �׽�Ʈ
			if (true == mSkill.cooldownReady)
			{
				mSkill.cooldownReady = false;
			}
		}
		break;
		case js::PlayerScript::eState::Dash:
		{			
			if (true == mDash.cooldownReady)
			{
				mDash.cooldownReady = false;
			}
		}
		break;
		case js::PlayerScript::eState::Special:
		{
			if (true == mSpecial.cooldownReady)
			{
				mSpecial.SetAble(false);
			}
		}
		break;
		case js::PlayerScript::eState::Ultimate:
		{
			if (true == mUltimate.cooldownReady)
			{
				mUltimate.cooldownReady = (false);
			}
		}
		break;
		}
	}

	// ���� �Ⱦ�
	void PlayerScript::shoot(ArcanaInfo& info)
	{
		// ���� ���
		float angle = calculateRotateAngle();
		
		// ����ü ã��
		int poolIndex = findProjectilePool();

		if (-1 != poolIndex)
		{
			// ����ü ȸ��
			projectileRotates(mProjectiles[poolIndex], angle);
			
			// ����ü�� �� ��ġ�� �ű��
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Transform* targetTr = mProjectiles[poolIndex]->GetOwner()->GetComponent<Transform>();
			targetTr->SetPosition(tr->GetPosition());

			mProjectiles[poolIndex]->ActiveArcana(info);
		}
		
	}

	void PlayerScript::calculateMouseDirection()
	{
		// ���콺 ���� ���ϱ�
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector3 myPosistion = myTr->GetPosition();
		Vector3 mousePosition = Input::GetMouseWorldPosition();
		Vector3 myDir = mousePosition - myPosistion;
		mMouseDir = Vector2(myDir.x, myDir.y);
		mMouseDir.Normalize();
	}
	float PlayerScript::calculateRotateAngle()
	{
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		float angle = atan2(mMouseDir.y, mMouseDir.x) - atan2(myTr->Up().y, myTr->Up().x);
		return angle;
	}
	void PlayerScript::setPlayerDirection(float angle)
	{
		//  ���� ��ȯ :  TOP | RIGHT | BOTTOM | LEFT 
		if ((TOP + 0.78) >= angle && (TOP - 0.78) <= angle)
			mMoveDir = Vector2(0, 1);
		else if ((RIGHT + 0.78) >= angle && (RIGHT - 0.78) <= angle)
			mMoveDir = Vector2(1, 0);
		else if ((BOTTOM + 0.78) >= angle && (BOTTOM - 0.78) <= angle)
			mMoveDir = Vector2(0, -1);
		else
			mMoveDir = Vector2(-1, 0);
	}

	int PlayerScript::findProjectilePool()
	{
		for (int index = 0; index < PROJECTILE_POOL; ++index)
		{
			// ������ ��������
			if (nullptr == mProjectiles[index])
				continue;
			// ������̸� ��������
			if (mProjectiles[index]->IsReady())
			{
				return index;
			}
			else
			{
				if (index == 63)
					int a = 0;
			}
			/*projectileRotate(angle);
			activeProjectile();*/
		}
		return -1;
	}
	void PlayerScript::projectileRotates(ArcanaScript* target, float angle)
	{
		Transform* targetTr = target->GetOwner()->GetComponent<Transform>();
		targetTr->SetRotation(Vector3(0.0f, 0.0f, angle));
	}
	
	void PlayerScript::playAnimation(eState changeState)
	{

		Animator* animator = GetOwner()->GetComponent<Animator>();

		// �÷��̾� ���� ����
		float angle = calculateRotateAngle();
		setPlayerDirection(angle);

		// �ִϸ��̼� ����
		switch (changeState)
		{
		case js::PlayerScript::eState::Idle:
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerIdleDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerIdleRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerIdleLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerIdleUp");
		}
			break;
		case js::PlayerScript::eState::Move:
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerRunDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerRunRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerRunLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerRunUp");
		}
			break;
		case js::PlayerScript::eState::AA:
		{
			playBasicMotion();
		}
			break;
		case js::PlayerScript::eState::Skill:
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerKickDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerKickRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerKickLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerKickUp");
		}
			break;
		case js::PlayerScript::eState::Dash:	// �Ⱦ�
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerDashDown", false);
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerDashRight", false);
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerDashLeft", false);
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerDashUp", false);
		}
			break;
		case js::PlayerScript::eState::Special:
		{
			if (1 == mMoveDir.y)
				animator->Play(L"PlayerGroundSlamUp", false);
			else
				animator->Play(L"PlayerGroundSlamDown", false);
		}
			break;
		case js::PlayerScript::eState::Ultimate:
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerAOEDown", false);
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerAOERight", false);
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerAOELeft", false);
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerAOEUp", false);
		}
			break;
		}

		// ���� ����
		mState = changeState;
	}
	void PlayerScript::playBasicMotion()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (true == mBasicAnimationType)
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerBackhandDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerBackhandRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerBackhandLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerBackhandUp");
			mBasicAnimationType = false;
		}
		else
		{
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerForehandDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerForehandRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerForehandLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerForehandUp");
			mBasicAnimationType = true;
		}
	}
	void PlayerScript::playDashMotion()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		mMoveDir.Normalize();
		if (Vector2(V2DOWN) == mMoveDir)
			animator->Play(L"PlayerDashDown", false);
		if (Vector2(V2RIGHT) == mMoveDir)
			animator->Play(L"PlayerDashRight", false);
		if (Vector2(V2LEFT) == mMoveDir)
			animator->Play(L"PlayerDashLeft", false);
		if (Vector2(V2UP) == mMoveDir)
			animator->Play(L"PlayerDashUp", false);
		mState = eState::Dash;
	}
	void PlayerScript::playerRush()
	{
		// �̵�
		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		myRigidbody->SetVelocity(mMouseDir * 11.0f);
	}
	void PlayerScript::addForce()
	{
		Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
		rigidbody->SetVelocity(mMoveDir * 56);
	}

	void PlayerScript::comboDelayOnCheck()
	{
		// ���ð��� �������� Ȯ��
		
	}

	bool PlayerScript::comboCountOutCheck()
	{
		if (mCurComboCount >= mMaxComboCount)
		{
			comboReset();
			return true;
		}
		return false;
	}

	bool PlayerScript::comboValidOutCheck()
	{
		if (mComboCurrentValidTime >= mComboValidTime)
		{			
			comboReset();
			return true;
		}
		return false;
	}

	void PlayerScript::comboReset()
	{
		// ���� �ʱ�ȭ
		mAA.cooldownReady = false;	// ��Ÿ ��ٿ� ����
		mComboProcess = false;		// �޺� ���� ����
		mComboDelay = false;		// �޺� ���ð� �ʱ�ȭ
		// ���� �ʱ�ȭ
		mComboCurrentValidTime = 0.0f;
		mComboCurrentDelayTime = 0.0f;
		mCurComboCount = 0;
	}

}