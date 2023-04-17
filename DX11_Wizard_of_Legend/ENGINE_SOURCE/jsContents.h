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
	// ī�װ�
	eArcanaCategory category;
	// ��� Ÿ��
	eArcanaType arcanaType;
	// ���װ�
	eStagger stagger;
	// ���ط� = ä��
	float damage;
	// ��Ÿ�
	float range;
	// ����ü ����
	int maxCount;
	int curCount;
	// ��� ����
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
	float regHp;	// ä�� ���

	float power;	// ���ط� ���� ���� | default = 1.0
	float criticalChance;
	float criticalDamage;

	float moveSpeed;
};