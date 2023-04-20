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
	int maxCount;
	int curCount;
	float cooldownTime;
	float currentTime;
	bool cooldownReady;
public:
	ArcanaInfo()
		: spellStat{}, maxCount(1), curCount(0), cooldownTime(1.0f), currentTime(0.0f), cooldownReady(true)
	{
	}
	void SetAble(bool trigger) { cooldownReady = trigger; }
};

struct Stat
{
	int level;
	float maxExp;
	float curExp;
	float gold;

	float maxHp;
	float curHp;
	float regHp;	// ä�� ���

	float power;	// ���ط� ���� ���� | default = 1.0
	float criticalChance;
	float criticalDamage;

	float moveSpeed;
};