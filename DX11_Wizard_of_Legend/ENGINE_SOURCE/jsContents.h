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
	// 기본
	bool cooldownReady;				// 재사용 준비됨
	float cooldownTime;				// 스킬 쿨다운
	float currentTime;

	// 연계기	
	bool comboDelay;				// 콤보 딜레이	
	bool comboProcess;				// 콤보 진행	
	int maxComboCount;				// 콤보 횟수
	int curComboCount;
	float comboValidTime;			// 콤보 유지 시간
	float comboCurrentValidTime;
	float comboDelayTime;			// 콤보 딜레이 시간
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
	float regHp;	// 채력 재생
	float moveSpeed;
};
struct OffenceStat
{
	float power;	// 피해량 증가 비율 | default = 1.0
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