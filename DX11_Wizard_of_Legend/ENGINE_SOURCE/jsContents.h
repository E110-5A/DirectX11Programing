#pragma once


#define PROJECTILE_POOL 64

// contents enum
enum class elStagger
{
	Light,
	Normal,
	Heave,
};
enum class eArcanaState
{
	Active,
	Disabled,
};
enum class elArcanaType
{
	AA,
	Skill,
	Dash,
	Special,
	Ultimate,
	End,
};
enum class elArcanaCategory
{
	Melee,
	Projectile,
	Dash,
	End,
};

struct lArcanaStat
{
	elArcanaCategory category;	// �ٰŸ�, ���Ÿ� ����
	elArcanaType arcanaType;		// ��ų Ÿ�� ����
	elStagger stagger;			// ������ ����
	float damage;
	float moveSpeed;
	float spellRange;			// ���Ÿ� ��� ��Ÿ�

public:
	lArcanaStat()
		: category(elArcanaCategory::Melee), arcanaType(elArcanaType::AA), stagger(elStagger::Light)
		, damage(0.0f), moveSpeed(0.0f), spellRange(0.0f)
	{}
};
struct lArcanaInfo
{
	// arcana Script���� ���
	lArcanaStat spellStat;

	// player Script ���� ���
	// �⺻
	bool cooldownReady;				// ���� �غ��
	float cooldownTime;				// ��ų ��ٿ�
	float currentTime;

	// �����	
	bool comboDelay;				// �޺� ������	
	bool comboProcess;				// �޺� ����	
	int maxComboCount;				// �޺� Ƚ��
	int curComboCount;
	float comboValidTime;			// �޺� ���� �ð�
	float comboCurrentValidTime;
	float comboDelayTime;			// �޺� ������ �ð�
	float comboCurrentDelayTime;

public:
	lArcanaInfo()
		: spellStat{}, cooldownReady(true), cooldownTime(0.0f), currentTime(0.0f)
		, comboDelay(false), comboProcess(false), maxComboCount(0), curComboCount(0)
		, comboValidTime(0.0f), comboCurrentValidTime(0.0f), comboDelayTime(0.0f), comboCurrentDelayTime(0.0f)
	{
	}
	void SetAble(bool trigger) { cooldownReady = trigger; }
};

#pragma region Creature Stat
struct HealthStat
{
	float maxHp;
	float curHp;
	float regHp;	// ä�� ���
	float moveSpeed;
};
struct OffenceStat
{
	float power;	// ���ط� ���� ���� | default = 1.0
	float criticalChance;
	float criticalDamage;
};
#pragma endregion

// ��� �ɵ�?
struct PlayerInfo
{
	int level;
	float maxExp;
	float curExp;
	float gold;
};


//=========================================================================================\\

// ����ü ���� (On, Off)
enum class eProjectileState
{
	Active,
	Disabled,
};
enum class eArcanaCategory
{
	Melee,
	Projectile,
	Dash,
	End,
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

struct ArcanaStat
{
	float	damage;						// ���ط�
	float	stagger;					// ������ġ
	float	moveSpeed;					// ����ü �ӵ�
	float	spellRange;					// ����ü ��Ÿ�
	float	projectileDelayTime;		// �޺� ������ �ð�
	float	projectileCurrentDelayTime;
	int		maxProjectile;				// ����ü ����
	int		curProjectile;
public:
	ArcanaStat()
		: damage(0.0f), stagger(0.0f), moveSpeed(0.0f), spellRange(0.0f), 
		projectileDelayTime(0.0f), projectileCurrentDelayTime(0.0f), maxProjectile(0), curProjectile(0)
	{}
};
struct ArcanaInfo
{
	eArcanaName		name;
	eArcanaCategory category;		// �ٰŸ�, ���Ÿ� ����
	eArcanaType		type;			// ��ų Ÿ��
	ePlayerMotion	motion;
	ePlayerBindSlot slot;
	bool			cooldownReady;	// ���� �غ��	
	float			cooldownTime;	// ��ų ��ٿ�
	float			currentTime;
	
public:
	ArcanaInfo()
		: name(eArcanaName::WindSlash), category(eArcanaCategory::Melee), type(eArcanaType::BasicArcana)
		, motion(ePlayerMotion::Basic), slot(ePlayerBindSlot::None), cooldownReady(true), cooldownTime(0.0f), currentTime(0.0f)
	{}
};

// å�� ������ ��� Arcana�� ������ ������ ����
// �÷��̾�� å�� �������κ��� Arcana ������ �μ��ΰ�޾� ��ųŰ�� ���ε���
// �ϴ� �÷��̾ ��� �˰��ְ� ���鿹��
struct Arcana
{
	ArcanaStat* arcanaStat;
	ArcanaInfo* arcanaInfo;
public:
	Arcana()
		: arcanaStat(nullptr), arcanaInfo(nullptr)
	{}
	~Arcana()
	{
		delete arcanaStat;
		delete arcanaInfo;
	}
};

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
		delete arcanaBasic;
		delete arcanaDash;
		delete arcanaSignature;
		delete arcanaStandardA;
		delete arcanaStandardB;
		delete arcanaStandardC;
		delete arcanaStandardD;
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
