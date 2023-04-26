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
	elArcanaCategory category;	// 근거리, 원거리 구분
	elArcanaType arcanaType;		// 스킬 타입 구분
	elStagger stagger;			// 경직도 구분
	float damage;
	float moveSpeed;
	float spellRange;			// 원거리 기술 사거리

public:
	lArcanaStat()
		: category(elArcanaCategory::Melee), arcanaType(elArcanaType::AA), stagger(elStagger::Light)
		, damage(0.0f), moveSpeed(0.0f), spellRange(0.0f)
	{}
};
struct lArcanaInfo
{
	// arcana Script에서 사용
	lArcanaStat spellStat;

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
	float regHp;	// 채력 재생
	float moveSpeed;
};
struct OffenceStat
{
	float power;	// 피해량 증가 비율 | default = 1.0
	float criticalChance;
	float criticalDamage;
};
#pragma endregion

// 없어도 될듯?
struct PlayerInfo
{
	int level;
	float maxExp;
	float curExp;
	float gold;
};


//=========================================================================================\\

// 투사체 상태 (On, Off)
enum class eProjectileState
{
	Active,
	Disabled,
};
enum class eArcanaType
{
	BasicArcana,		// 기본공격에 해당, 낮은 경직도
	DashArcana,			// 대시공격에 해당
	StandardArcana,		// 일반기술에 해당, 중간 경직도
	SignatureArcana,	// 특수기술에 해당, 높은 경직도, 마나를 채울경우 쿨다운 초기화 및 강화됨
};
// 아르카나 처음부터 설계하기
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
	float	damage;						// 피해량
	float	stagger;					// 경직수치
	float	moveSpeed;					// 투사체 속도
	float	spellRange;					// 투사체 사거리
	float	projectileDelayTime;		// 콤보 딜레이 시간
	float	projectileCurrentDelayTime;
	int		maxProjectile;				// 투사체 개수
	int		curProjectile;
public:
	ArcanaStat()
		: damage(0.0f), stagger(0.0f), moveSpeed(0.0f), spellRange(0.0f), 
		projectileDelayTime(0.0f), projectileCurrentDelayTime(0.0f), maxProjectile(0), curProjectile(0)
	{}
};
struct ArcanaInfo
{
	std::wstring	arcanaName;		// 애니메이션 이름
	eArcanaCategory category;		// 근거리, 원거리 구분
	eArcanaType		type;			// 스킬 타입
	bool			cooldownReady;	// 재사용 준비됨
	
	float			cooldownTime;	// 스킬 쿨다운
	float			currentTime;
	
public:
	ArcanaInfo()
		: category(eArcanaCategory::Melee), arcanaName{}, cooldownReady(true)
		, cooldownTime(0.0f), currentTime(0.0f)
	{}
};

// 책과 상인은 모든 Arcana의 정보를 가지고 있음
// 플레이어는 책과 상인으로부터 Arcana 정보를 인수인계받아 스킬키에 바인딩함
// 일단 플레이어가 몇개를 알고있게 만들예정
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