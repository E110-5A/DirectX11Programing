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
enum class eArcanaType
{
	BasicArcana,		// �⺻���ݿ� �ش�, ���� ������
	DashArcana,			// ��ð��ݿ� �ش�
	StandardArcana,		// �Ϲݱ���� �ش�, �߰� ������
	SignatureArcana,	// Ư������� �ش�, ���� ������, ������ ä���� ��ٿ� �ʱ�ȭ �� ��ȭ��
};
// �Ƹ�ī�� ó������ �����ϱ�
#pragma region Arcana
enum class eArcanaCategory
{
	Melee,
	Projectile,
	Dash,
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
	std::wstring	arcanaName;		// �ִϸ��̼� �̸�
	eArcanaCategory category;		// �ٰŸ�, ���Ÿ� ����
	eArcanaType		type;			// ��ų Ÿ��
	bool			cooldownReady;	// ���� �غ��
	
	float			cooldownTime;	// ��ų ��ٿ�
	float			currentTime;
	
public:
	ArcanaInfo()
		: category(eArcanaCategory::Melee), arcanaName{}, cooldownReady(true)
		, cooldownTime(0.0f), currentTime(0.0f)
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
	Arcana* arcanaStandardA;
	Arcana* arcanaStandardB;
	Arcana* arcanaStandardC;
	Arcana* arcanaStandardD;
	Arcana* arcanaSignature;

	Inventory()
		:relics{}, arcanaBasic(nullptr), arcanaDash(nullptr),
		arcanaStandardA(nullptr), arcanaStandardB(nullptr), arcanaStandardC(nullptr), arcanaStandardD(nullptr), arcanaSignature(nullptr)
	{}
};