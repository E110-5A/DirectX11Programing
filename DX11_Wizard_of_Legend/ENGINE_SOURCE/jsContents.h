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
	eArcanaCategory category;	// 근거리, 원거리 구분
	eArcanaType arcanaType;		// 스킬 타입 구분
	eStagger stagger;			// 경직도 구분
	float damage;
	float moveSpeed;
	float spellRange;			// 원거리 기술 사거리

public:
	ArcanaStat()
		: category(eArcanaCategory::Melee), arcanaType(eArcanaType::AA), stagger(eStagger::Light)
		, damage(0.0f), moveSpeed(0.0f), spellRange(0.0f)
	{}
};


struct ArcanaInfo
{
	// arcana Script에서 사용
	ArcanaStat spellStat;

	// player Script 에서 사용
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
	float regHp;	// 채력 재생

	float power;	// 피해량 증가 비율 | default = 1.0
	float criticalChance;
	float criticalDamage;

	float moveSpeed;
};