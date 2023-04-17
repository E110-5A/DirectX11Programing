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
		, mProjectiles{}
		, mAA{}
		, mSkill{}
		, mDash{}
		, mSpecial{}
		, mUltimate{}
		, mProjectile(nullptr)	// �Ⱦ�
		, mProjectileType(eArcanaCategory::Melee)
	{
	}
	
	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
		createAnimation();
		addEvent();
		// ��� �����ϱ�
		// �ٰŸ� ��Ÿ (�޺� ��� ������!)
		initializeArcana(mAA, eArcanaCategory::Melee, eArcanaType::AA, eStagger::Light, 6.0f, 30.0f, 1, 0);
		
		// ��ȭ�� 3�� ������ (����)
		initializeArcana(mSkill, eArcanaCategory::Projectile, eArcanaType::Skill, eStagger::Normal, 6.5f, 20.0f, 1, 3.0f);

		// ����� ��ġ����?
		initializeArcana(mDash, eArcanaCategory::Melee, eArcanaType::Dash, eStagger::Light, 3.0f, 60.0f, 1, 1.0f);

		// ������ Dragon_Arc
		initializeArcana(mSpecial, eArcanaCategory::Projectile, eArcanaType::Special, eStagger::Normal, 6.5f, 20.0f, 1, 3.0f);
		// ū���ѹ� Shearing_Chain
		initializeArcana(mUltimate, eArcanaCategory::Projectile, eArcanaType::Ultimate, eStagger::Heave, 6.5f, 20.0f, 1, 3.0f);
	}

	void PlayerScript::Update()
	{
		// ��ٿ�
		//cooldown();
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
		//skillProcess();

		calculateMouseDir();

		if (Input::GetKey(eKeyCode::K))
		{
			GetOwner()->Kill();
		}
		if (Input::GetKey(eKeyCode::L))
		{
			GetOwner()->Alive();
		}
	}

	void PlayerScript::Render()
	{
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
			animator->Create(L"PlayerRunDown", texture, Vector2(0.0f, 49.0f), defaultSize, Vector2::Zero, 10, 0.1f);
			animator->Create(L"PlayerRunRight", texture, Vector2(0.0f, 97.0f), defaultSize, Vector2::Zero, 10, 0.1f);
			animator->Create(L"PlayerRunLeft", texture, Vector2(0.0f, 145.0f), defaultSize, Vector2::Zero, 10, 0.1f);
			animator->Create(L"PlayerRunUp", texture, Vector2(0.0f, 193.0f), defaultSize, Vector2::Zero, 10, 0.1f);
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
			animator->Create(L"PlayerDashDown", texture, Vector2(0.0f, 242.0f), defaultSize, Vector2::Zero, 4, 0.07f);
			animator->Create(L"PlayerDashRight", texture, Vector2(0.0f, 290.0f), defaultSize, Vector2::Zero, 6, 0.07f);
			animator->Create(L"PlayerDashLeft", texture, Vector2(0.0f, 338.0f), defaultSize, Vector2::Zero, 6, 0.07f);
			animator->Create(L"PlayerDashUp", texture, Vector2(0.0f, 386.0f), defaultSize, Vector2::Zero, 5, 0.07f);
		}
		// Basic
		{
			animator->Create(L"PlayerBackhandDown", texture, Vector2(0.0f, 435.0f), defaultSize, Vector2::Zero, 9, 0.05f);
			animator->Create(L"PlayerBackhandRight", texture, Vector2(0.0f, 483.0f), defaultSize, Vector2::Zero, 9, 0.05f);
			animator->Create(L"PlayerBackhandLeft", texture, Vector2(0.0f, 531.0f), defaultSize, Vector2::Zero, 9, 0.05f);
			animator->Create(L"PlayerBackhandUp", texture, Vector2(0.0f, 579.0f), defaultSize, Vector2::Zero, 9, 0.05f);
			animator->Create(L"PlayerForehandDown", texture, Vector2(0.0f, 628.0f), defaultSize, Vector2::Zero, 9, 0.05f);
			animator->Create(L"PlayerForehandRight", texture, Vector2(0.0f, 676.0f), defaultSize, Vector2::Zero, 8, 0.05f);
			animator->Create(L"PlayerForehandLeft", texture, Vector2(0.0f, 724.0f), defaultSize, Vector2::Zero, 8, 0.05f);
			animator->Create(L"PlayerForehandUp", texture, Vector2(0.0f, 772.0f), defaultSize, Vector2::Zero, 12, 0.05f);
		}
		// Slam
		{
			animator->Create(L"PlayerGroundSlamDown", texture, Vector2(0.0f, 821.0f), defaultSize, Vector2::Zero, 10, 0.1f);
			animator->Create(L"PlayerGroundSlamUp", texture, Vector2(0.0f, 869.0f), defaultSize, Vector2::Zero, 10, 0.1f);
		}
		// AOE
		{
			animator->Create(L"PlayerAOEDown", texture, Vector2(0.0f, 918.0f), defaultSize, Vector2::Zero, 9, 0.1f);
			animator->Create(L"PlayerAOERight", texture, Vector2(0.0f, 966.0f), defaultSize, Vector2::Zero, 12, 0.1f);
			animator->Create(L"PlayerAOELeft", texture, Vector2(0.0f, 1014.0f), defaultSize, Vector2::Zero, 12, 0.1f);
			animator->Create(L"PlayerAOEUp", texture, Vector2(0.0f, 1062.0f), defaultSize, Vector2::Zero, 11, 0.1f);
		}
		// Kick
		{
			animator->Create(L"PlayerKickDown", texture, Vector2(0.0f, 1159.0f), defaultSize, Vector2::Zero, 11, 0.1f);
			animator->Create(L"PlayerKickLeft", texture, Vector2(0.0f, 1255.0f), defaultSize, Vector2::Zero, 9, 0.1f);
			animator->Create(L"PlayerKickRight", texture, Vector2(0.0f, 1207.0f), defaultSize, Vector2::Zero, 9, 0.1f);
			animator->Create(L"PlayerKickUp", texture, Vector2(0.0f, 1303.0f), defaultSize, Vector2::Zero, 8, 0.1f);
		}

		animator->Play(L"PlayerIdleDown");
	}
	void PlayerScript::addEvent()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		//animator->GetStartEvent(L"MoveDown") = std::bind(&PlayerScript::Start, this);
		//animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		//animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		//animator->GetActionEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);

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
			animator->GetCompleteEvent(L"PlayerBackhandDown") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandRight") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandLeft") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerBackhandUp") = std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerBackhandDown", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandRight", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandLeft", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerBackhandUp", 3) = std::bind(&PlayerScript::playerRush, this);

			animator->GetCompleteEvent(L"PlayerForehandDown") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandRight") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandLeft") = std::bind(&PlayerScript::setIdle, this);
			animator->GetCompleteEvent(L"PlayerForehandUp") = std::bind(&PlayerScript::setIdle, this);
			animator->GetActionEvent(L"PlayerForehandDown", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandRight", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandLeft", 3) = std::bind(&PlayerScript::playerRush, this);
			animator->GetActionEvent(L"PlayerForehandUp", 3) = std::bind(&PlayerScript::playerRush, this);
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
		skill.cooldown = cooldown;
		skill.currentTime = 0.0f;
		skill.able = true;
	}

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

		if (Input::GetKey(eKeyCode::LBTN))
		{
			playAnimation(eState::AA);
		}
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{
			playAnimation(eState::Skill);
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
		if (Input::GetKeyDown(eKeyCode::F))
		{
			playAnimation(eState::Special);
		}
		if (Input::GetKeyDown(eKeyCode::Q))
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
			mMoveDir = Vector2(0, -1);
		}
		if (Input::GetKey(eKeyCode::D))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Right() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(1, 0);
		}
		if (Input::GetKey(eKeyCode::A))
		{
			Vector3 pos = tr->GetPosition();
			pos += -tr->Right() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(-1, 0);
		}
		if (Input::GetKey(eKeyCode::W))
		{
			Vector3 pos = tr->GetPosition();
			pos += tr->Up() * mMoveSpeed * Time::DeltaTime();
			tr->SetPosition(pos);
			mMoveDir = Vector2(0, 1);
		}

		// �ִϸ��̼�
		if (Input::GetKey(eKeyCode::LBTN))
		{
			playAnimation(eState::AA);
		}
		if (Input::GetKeyDown(eKeyCode::RBTN))
		{
			playAnimation(eState::Skill);
		}
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
		if (Input::GetKeyDown(eKeyCode::F))
		{
			playAnimation(eState::Special);
		}
		if (Input::GetKeyDown(eKeyCode::Q))
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
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
	}

	void PlayerScript::Skill()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
	}

	void PlayerScript::Dash()
	{

	}

	void PlayerScript::Special()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
	}

	void PlayerScript::Ultimate()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			playAnimation(eState::Dash);
		}
	}



	

	void PlayerScript::playAnimation(eState changeState)
	{

		Animator* animator = GetOwner()->GetComponent<Animator>();

		// �÷��̾� ���� ����
		float angle = calculateRotate();
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
			if (Vector2(V2DOWN) == mMoveDir)
				animator->Play(L"PlayerBackhandDown");
			if (Vector2(V2RIGHT) == mMoveDir)
				animator->Play(L"PlayerBackhandRight");
			if (Vector2(V2LEFT) == mMoveDir)
				animator->Play(L"PlayerBackhandLeft");
			if (Vector2(V2UP) == mMoveDir)
				animator->Play(L"PlayerBackhandUp");

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
		case js::PlayerScript::eState::Dash:
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

	// able : false �� ��� ��ٿ� ����
	void PlayerScript::cooldown()
	{
		// ��ų�� ���ǰ� �� �Ŀ� able�� false������


		// RBTN
		if (false == mSkill.able)
		{
			mSkill.currentTime += Time::DeltaTime();

			if (mSkill.currentTime >= mSkill.cooldown)
			{
				mSkill.able = true;
				mSkill.currentTime = 0.0f;
			}
		}
		
		// SPACE
		if (false == mDash.able)
		{
			mDash.currentTime += Time::DeltaTime();

			if (mDash.currentTime >= mDash.cooldown)
			{
				mDash.able = true;
				mDash.currentTime = 0.0f;
			}
		}

		// F
		if (false == mSpecial.able)
		{
			mSpecial.currentTime += Time::DeltaTime();

			if (mSpecial.currentTime >= mSpecial.cooldown)
			{
				mSpecial.able = true;
				mSpecial.currentTime = 0.0f;
			}
		}

		// Q
		if (false == mUltimate.able)
		{
			mUltimate.currentTime += Time::DeltaTime();

			if (mUltimate.currentTime >= mUltimate.cooldown)
			{
				mUltimate.able = true;
				mUltimate.currentTime = 0.0f;
			}
		}
	}

	void PlayerScript::skillProcess()
	{
		// ��ǥ
		// ��ų ���� ����� (�̺�Ʈ �Ⱦ���)

		// ��ٿ��� Ȯ���� �ʿ� ����, ���ʿ� ��ٿ��̸� ���°� ��������� ����

		cooldown();

		// �޺� �ʱ�ȭ
		if (0 >= mComboCurrentTime)
			mComboCurrentTime = mComboValidTime;

		switch (mState)
		{
			// �޺� �����
		case js::PlayerScript::eState::AA:
		{
			mComboCurrentTime -= Time::DeltaTime();
			// 1 ���� �޺� ī��Ʈ Ȯ�� (������ 3����)
			if (mCurrentCount < mComboCount)
			{
				// ��ų ī��Ʈ Ȯ��
				if (mAA.maxCount > mAA.curCount)
				{
					// 2 �޺� ��ȿ�ð� Ȯ��
					if (0 <= mComboCurrentTime)
					{
						++mCurrentCount;
						// ���� �߽�
						shoot(mAA);
					}
				}
			}
			else
			{
				mAA.curCount = 0;
				// �޺��� ��ȿ���� ������ ��ٿ� ������
				mAA.SetAble(false);
			}
		}
		break;
		case js::PlayerScript::eState::Skill:
		{
			// ��밡���� ����..�� ���԰���?
			if (false == mSkill.able)
				return;

			if (true == mSkill.able)
			{
				// �ش� ��ų�� ī��Ʈ�� �ִ븦 �ѱ���
				if (mSkill.curCount >= mSkill.maxCount)
				{
					// ī��Ʈ �ʱ�ȭ�ϰ� ��ٿ���·� ����
					mSkill.curCount = 0;
					mSkill.SetAble(false);
					break;
				}

				++mSkill.curCount;
				shoot(mSkill);
			}
		}
		break;
		case js::PlayerScript::eState::Dash:
		{
			if (false == mDash.able)
				return;

			if (true == mDash.able)
			{
				// ��ų ī��Ʈ Ȯ��
				if (mDash.maxCount > mDash.curCount)
				{
					++mDash.curCount;
					// ���� �߽�
					shoot(mDash);
				}
				else
				{
					mDash.curCount = 0;
					mDash.SetAble(false);
				}
			}
		}
		break;
		case js::PlayerScript::eState::Special:
		{
			if (false == mSpecial.able)
				return;
			if (true == mSpecial.able)
			{
				// ��ų ī��Ʈ Ȯ��
				if (mSpecial.maxCount > mSpecial.curCount)
				{
					++mSpecial.curCount;
					// ���� �߽�
					shoot(mSpecial);
				}
				else
				{
					mSpecial.curCount = 0;
					mSpecial.SetAble(false);
				}
			}
		}
		break;
		case js::PlayerScript::eState::Ultimate:
		{
			if (false == mUltimate.able)
				return;
			if (true == mUltimate.able)
			{
				// ��ų ī��Ʈ Ȯ��
				if (mUltimate.maxCount > mUltimate.curCount)
				{
					++mUltimate.curCount;
					// ���� �߽�
					shoot(mUltimate);
				}
				else
				{
					mUltimate.curCount = 0;
					mUltimate.SetAble(false);
				}
			}
		}
		break;
		}

		//shoot();
	}

	void PlayerScript::shoot(ArcanaInfo& info)
	{
		// ���� ���
		float angle = calculateRotate();
		
		// ����ü ã��
		int poolIndex = findProjectilePool();

		if (-1 != poolIndex)
		{
			// ����ü ȸ��
			projectileRotates(mProjectiles[poolIndex], angle);
			//activeProjectiles(mProjectiles[poolIndex]);
			
			// ����ü�� �� ��ġ�� �ű��
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Transform* targetTr = mProjectiles[poolIndex]->GetOwner()->GetComponent<Transform>();
			targetTr->SetPosition(tr->GetPosition());

			// ����ü Ȱ��ȭ
			//mProjectiles[poolIndex]->ActiveProjectile(mProjectileType);

			mProjectiles[poolIndex]->ActiveArcana(info);
		}
		
	}


	void PlayerScript::calculateMouseDir()
	{
		// ���콺 ���� ���ϱ�
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		Vector3 myPosistion = myTr->GetPosition();
		Vector3 mousePosition = Input::GetMouseWorldPosition();
		Vector3 myDir = mousePosition - myPosistion;
		mMouseDir = Vector2(myDir.x, myDir.y);
		mMouseDir.Normalize();
	}
	float PlayerScript::calculateRotate()
	{
		Transform* myTr = GetOwner()->GetComponent<Transform>();
		float angle = atan2(mMouseDir.y, mMouseDir.x) - atan2(myTr->Up().y, myTr->Up().x);
		return angle;
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
	void PlayerScript::playerRush()
	{
		// �̵�
		Rigidbody* myRigidbody = GetOwner()->GetComponent<Rigidbody>();
		myRigidbody->SetVelocity(mMouseDir * 11.0f);
	}

	void PlayerScript::projectileRotates(ArcanaScript* target, float angle)
	{
		Transform* targetTr = target->GetOwner()->GetComponent<Transform>();
		targetTr->SetRotation(Vector3(0.0f, 0.0f, angle));
	}
	void PlayerScript::activeProjectiles(ArcanaScript* target)
	{
		// ����ü�� �� ��ġ�� �ű��
		Transform * tr = GetOwner()->GetComponent<Transform>();
		Transform* targetTr = target->GetOwner()->GetComponent<Transform>();
		targetTr->SetPosition(tr->GetPosition());

		// ����ü ���� �ʱ�ȭ
		target->ActiveProjectile(mProjectileType);
	}


	void PlayerScript::setStateDash()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Animator* animator = GetOwner()->GetComponent<Animator>();

		
		mState = eState::Dash;
	}

	void PlayerScript::retIdle()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

		mState = eState::Idle;
		if (Vector2(V2DOWN) == mMoveDir)
		{
			animator->Play(L"PlayerIdleDown");
		}
		if (Vector2(V2RIGHT) == mMoveDir)
		{
			animator->Play(L"PlayerIdleRight");
		}
		if (Vector2(V2LEFT) == mMoveDir)
		{
			animator->Play(L"PlayerIdleLeft");
		}
		if (Vector2(V2UP) == mMoveDir)
		{
			animator->Play(L"PlayerIdleUp");
		}
	}
	void PlayerScript::addForce()
	{
		Rigidbody* rigidbody = GetOwner()->GetComponent<Rigidbody>();
		rigidbody->SetVelocity(mMoveDir * 56);
	}	
}