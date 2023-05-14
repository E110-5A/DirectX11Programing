#pragma once


#define PROJECTILE_POOL 64


#pragma region Creature Stat
struct HealthStat
{
	float	curHp;
	float	maxHp;
	float	regHp;			// ä�� ���
	float	moveSpeed;
	float	curResistance;	// ���� ���� ��ġ : 0 �̵Ǹ� ������
	float	maxResistance;
	bool	standing;		// �˹� ����?
};
struct OffenceStat
{
	float power;			// ���ط� ���� ���� | default = 1.0
	float criticalChance;	
	float criticalDamage;
};
#pragma endregion

#pragma region Projectile
enum class eProjectileState
{
	Active,
	Disabled,
};
struct ProjectileStat
{
	float	damage;			// ���ط�
	float	stagger;		// ������ġ
	float	speed;			// ����ü �ӵ�
	float	range;			// ����ü ��Ÿ�
public:
	ProjectileStat()
		: damage(0.0f), stagger(0.0f), speed(0.0f), range(0.0f)
	{}
};
struct ProjectileConditionValue
{
	float			cooldownTime;				// ��ų ��ٿ�
	float			currentCooldownTime;
	float			delayTime;					// �޺� ������ �ð�
	float			currentDelayTime;
	int				maxCount;					// ����ü ����
	int				curCount;
	bool			cooldownReady;				// ��ų ���� ���� (false �� ��� �÷��̾� State ������ ����)
	bool			begin;						// ��ų ���� ���� (true �� ��� ��ų�� �����)
	bool			complete;					// ��ų ��� ���� (true �� ��� ���̻� ��ų�� ����ȵ�)
public:
	ProjectileConditionValue()
		: cooldownTime(0.0f), currentCooldownTime(0.0f), delayTime(0.0f), currentDelayTime(0.0f)
		, maxCount(0), curCount(0), cooldownReady(true), begin(false), complete(false)
	{}
};
#pragma endregion
#pragma region Arcana
enum class eArcanaCategory
{
	Melee,
	Range,
	Dash,
};
enum class eArcanaType
{
	BasicArcana,		// �⺻���ݿ� �ش�, ���� ������
	DashArcana,			// ��ð��ݿ� �ش�
	StandardArcana,		// �Ϲݱ���� �ش�, �߰� ������
	SignatureArcana,	// Ư������� �ش�, ���� ������, ������ ä���� ��ٿ� �ʱ�ȭ �� ��ȭ��
};
enum class eArcanaName
{
	None,
	// basic
	WindSlash,
	EarthKnuckles,
	// dash
	AirBurst,
	// standard & signature
	ShearingChain,
	ObsidianCascade,
	DragonArc,
	ExplodingFireball,
	IceSpear,
	CardicePrime,
};
enum class ePlayerMotion
{
	Dash,
	Basic,
	Backhand,
	Forehand,
	GroundSlam,
	AOE,
	Kick,
};
enum class eInventorySlot
{
	arcanaBasic,
	arcanaDash,
	arcanaSignature,
	arcanaStandardA,
	arcanaStandardB,
	arcanaStandardC,
	arcanaStandardD,
};
enum class ePlayerBindSlot
{
	None,
	LBtn,
	RBtn,
	Space,
	Q,
	F,
	R,
	End,
};
struct ArcanaInfo
{
	eArcanaName		name;
	eArcanaCategory category;					// �ٰŸ�, ���Ÿ� ����
	eArcanaType		type;						// ��ų Ÿ��
	ePlayerMotion	motion;
	ePlayerBindSlot slot;

public:
	ArcanaInfo()
		: name(eArcanaName::WindSlash), category(eArcanaCategory::Melee), type(eArcanaType::BasicArcana)
		, motion(ePlayerMotion::Basic), slot(ePlayerBindSlot::None)
	{}
};
struct Arcana
{
	ArcanaInfo*					arcanaInfo;
	ProjectileStat*				projectileStat;
	ProjectileConditionValue*	conditionValue;

public:
	Arcana()
		: arcanaInfo(nullptr), projectileStat(nullptr), conditionValue(nullptr)
	{}
	~Arcana()
	{
		if (nullptr != arcanaInfo)
		{
			delete arcanaInfo;
			arcanaInfo = nullptr;
		}
		if (nullptr != projectileStat)
		{
			delete projectileStat;
			projectileStat = nullptr;
		}		
		if (nullptr != conditionValue)
		{
			delete conditionValue;
			conditionValue = nullptr;
		}
	}
};
#pragma endregion

enum class eRelic
{
	ComboGloves,
	B,
	C,
	D,
};
struct Relic
{
	eRelic name;
};

struct Inventory
{
	std::vector<Relic*> relics;
	Arcana* arcanaBasic;
	Arcana* arcanaDash;
	Arcana* arcanaSignature;
	Arcana* arcanaStandardA;
	Arcana* arcanaStandardB;
	Arcana* arcanaStandardC;
	Arcana* arcanaStandardD;

public:
	Inventory()
		: relics{}, arcanaBasic(nullptr), arcanaDash(nullptr), arcanaSignature(nullptr)
		, arcanaStandardA(nullptr), arcanaStandardB(nullptr), arcanaStandardC(nullptr), arcanaStandardD(nullptr)
	{}
	~Inventory()
	{
		if (nullptr != arcanaBasic)
		{
			delete arcanaBasic;
			arcanaBasic = nullptr;
		}
		if (nullptr != arcanaDash)
		{
			delete arcanaDash;
			arcanaDash = nullptr;
		}
		
		if (nullptr != arcanaSignature)
		{
			delete arcanaSignature;
			arcanaSignature = nullptr;
		}
		
		if (nullptr != arcanaStandardA)
		{
			delete arcanaStandardA;
			arcanaStandardA = nullptr;
		}
		
		if (nullptr != arcanaStandardB)
		{
			delete arcanaStandardB;
			arcanaStandardB = nullptr;
		}
		
		if (nullptr != arcanaStandardC)
		{
			delete arcanaStandardC;
			arcanaStandardC = nullptr;
		}
		
		if (nullptr != arcanaStandardD)
		{
			delete arcanaStandardD;
			arcanaStandardD = nullptr;
		}
		
	}
	void AddArcana(Arcana* other)
	{
		// �Ƹ�ī�� Ÿ���� ���� �߰���

		// ���� �Ƹ�ī���� ������ ������
		// Basic
		if (eArcanaType::BasicArcana == other->arcanaInfo->type)
		{
			if (nullptr == arcanaBasic)
				arcanaBasic = other;
			else
				SwapArcana(eInventorySlot::arcanaBasic, other);
		}
		
		// Dash
		if (eArcanaType::DashArcana == other->arcanaInfo->type)
		{
			if (nullptr == arcanaDash)
				arcanaDash = other;
			else
				SwapArcana(eInventorySlot::arcanaDash, other);
		}
		// signature
		if (eArcanaType::SignatureArcana == other->arcanaInfo->type)
		{
			if (nullptr == arcanaSignature)
				arcanaSignature = other;
			else
				SwapArcana(eInventorySlot::arcanaSignature, other);
		}
		// Standard ������� ������ ä���, ������� ���ٸ� D�Ƹ�ī���� ����
		if (eArcanaType::StandardArcana == other->arcanaInfo->type)
		{
			if (nullptr == arcanaStandardA)
				arcanaStandardA = other;
			else if (nullptr == arcanaStandardB)
				arcanaStandardB = other;
			else if (nullptr == arcanaStandardC)
				arcanaStandardC = other;
			else if (nullptr == arcanaStandardD)
				arcanaStandardD = other;
			else
				SwapArcana(eInventorySlot::arcanaStandardD, other);
		}
	}
	// ���԰� �Ƹ�ī���� �Է��ϸ� �ش� �Ƹ�ī���� �κ��丮�� �����
	Arcana* SwapArcana(eInventorySlot slot, Arcana* other)
	{
		// �Է��� �Ƹ�ī���� �ش� ���Կ� �ش��ϴ� �Ƹ�ī���� ��ü�ϰ� ���� �Ƹ�ī���� ��ȯ��
		switch (slot)
		{
		case eInventorySlot::arcanaBasic:
		{
			Arcana* temp = arcanaBasic;
			arcanaBasic = other;
			return temp;
		}
			break;
		case eInventorySlot::arcanaDash:
		{
			Arcana* temp = arcanaDash;
			arcanaDash = other;
			return temp;
		}
			break;
		case eInventorySlot::arcanaSignature:
		{
			Arcana* temp = arcanaSignature;
			arcanaSignature = other;
			return temp;
		}
			break;
		case eInventorySlot::arcanaStandardA:
		{
			Arcana* temp = arcanaStandardA;
			arcanaStandardA = other;
			return temp;
		}
			break;
		case eInventorySlot::arcanaStandardB:
		{
			Arcana* temp = arcanaStandardB;
			arcanaStandardB = other;
			return temp;
		}
			break;
		case eInventorySlot::arcanaStandardC:
		{
			Arcana* temp = arcanaStandardC;
			arcanaStandardC = other;
			return temp;
		}
			break;
		case eInventorySlot::arcanaStandardD:
		{
			Arcana* temp = arcanaStandardD;
			arcanaStandardD = other;
			return temp;
		}
			break;
		}
	}
};
