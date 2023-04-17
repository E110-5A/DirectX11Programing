#pragma once


#define PROJECTILE_POOL 64

// contents enum
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
struct ArcanaInfo
{
	// 카테고리
	eArcanaCategory category;
	// 기술 타입
	eArcanaType arcanaType;
	// 스테거
	eStagger stagger;
	// 피해량 = 채력
	float damage;
	// 사거리
	float range;
	// 투사체 개수
	int maxCount;
	int curCount;
	// 기술 재사용
	float cooldown;
	float currentTime;
	bool able;
public:
	ArcanaInfo()
		: category(eArcanaCategory::Melee), arcanaType(eArcanaType::AA), stagger(eStagger::Light)
		, damage(5), range(100), maxCount(1), curCount(0), cooldown(1.0f), currentTime(0.0f), able(true)
	{
	}
	void SetAble(bool trigger) { able = trigger; }
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