#pragma once


#define PROJECTILE_POOL 64

// contents enum

enum class eArcanaState
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
	AA,
	Skill,
	Dash,
	Special,
	Ultimate,
	End,
};

enum class eStagger
{
	Light,
	Normal,
	Heave,
};

struct ArcanaStat
{
	eArcanaCategory category;	// �ٰŸ�, ���Ÿ� ����
	eArcanaType arcanaType;		// ��ų Ÿ�� ����
	eStagger stagger;			// ������ ����
	float damage;
	float moveSpeed;
	float spellRange;			// ���Ÿ� ��� ��Ÿ�

public:
	ArcanaStat()
		: category(eArcanaCategory::Melee), arcanaType(eArcanaType::AA), stagger(eStagger::Light)
		, damage(0.0f), moveSpeed(0.0f), spellRange(0.0f)
	{}
};


struct ArcanaInfo
{
	// arcana Script���� ���
	ArcanaStat spellStat;

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
	ArcanaInfo()
		: spellStat{}, cooldownReady(true), cooldownTime(0.0f), currentTime(0.0f)
		, comboDelay(false), comboProcess(false), maxComboCount(0), curComboCount(0)
		, comboValidTime(0.0f), comboCurrentValidTime(0.0f), comboDelayTime(0.0f), comboCurrentDelayTime(0.0f)
	{
	}
	void SetAble(bool trigger) { cooldownReady = trigger; }
};

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
struct PlayerInfo
{
	int level;
	float maxExp;
	float curExp;
	float gold;
};