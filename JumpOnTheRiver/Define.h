#pragma once
#include <string>

/// <summary>
/// 게임 내에서 쓰이는 모든 정의 (상수, 초깃값 등)
/// 
/// 2022.02.21 LeHideHome
/// </summary>

// 오브젝트들의 초기 위치

/// <summary>
/// 상수를 사용하기 위한 클래스. static const로 사용한다.
/// </summary>
class ConstValue
{
public:
	static const int StartPosX = 104;

	static const int PositiveY = 500-55;	// 현실의 지면
	static const int GroundY = 540;			// 절대적인 지면 (현실과 그림자의 중간)
	static const int NegativeY = 580+55;	// 그림자의 지면
};


// player 이동제한용
#define MIN_X 30
#define MAX_X 5700
#define MINOFFSET_X 26
#define MAXOFFSET_X 5704

// 점프용
#define GROUNDYPOS 400
#define GRAVITY 50.0f
#define JUMP_POWER 15.0f

// 카메라용
#define WIDTH 960
#define HEIGHT 540

// SoundManager
#define SOUND_MAX 1.0f
#define SOUND_MIN 0.0f
#define SOUND_DEFAULT 0.5f
#define SOUND_WEIGHT 0.1f

// window process
#define SCRWIDTH 1920
#define SCRHEIGHT 1080

#define MAX_LOADSTRING 100

// 가상키보드 조작 (16진수로 바꿀 것)
#define VK__0 48
#define VK__1 49
#define VK__2 50
#define VK__3 51
#define VK__4 52
#define VK__5 53
#define VK__6 54
#define VK__7 55
#define VK__8 56
#define VK__9 57
#define VK__A 65
#define VK__B 66
#define VK__C 67
#define VK__D 68
#define VK__E 69
#define VK__F 70
#define VK__G 71
#define VK__H 72
#define VK__I 73
#define VK__J 74
#define VK__K 75
#define VK__L 76
#define VK__M 77
#define VK__N 78
#define VK__O 79
#define VK__P 80
#define VK__Q 81
#define VK__R 82
#define VK__S 83
#define VK__T 84
#define VK__U 85
#define VK__V 86
#define VK__W 87
#define VK__X 88
#define VK__Y 89
#define VK__Z 90

// #define VK_F1 = 112
// #define VK_F2 = 113
// #define VK_F3 = 114

// 여러 종류의 오브젝트를 분류를 했다!
// 플레이어와 오브젝트를 다른 ENUM CLASS로 갖고 있어야할 것 같아. 

enum class PLAYER_TYPE
{
	GIRL,			// 소녀
	SHADOW,			// 그림자
};

enum class OBJECT_TYPE
{
	/// 배경
	background_sky,				   // 하늘 배경
	background_river,			   // 강 배경
	background_center,			   // 배경 중간 선
	
	background_cloud,				// 배경 구름 

	background_gameTitle,			   // 타이틀 화면
	background_startCutScene1,		   // 시작 컷씬 1
	background_startCutScene2,		   // 시작 컷씬 2
	background_startCutScene3,	       // 시작 컷씬 3
	background_endingCutScene1,		   // 엔딩 컷씬 1
	background_endingCutScene2,		   // 엔딩 컷씬 2
	background_endingCutScene3,		   // 엔딩 컷씬 3
	background_endingCredit,		   // 엔딩 크레딧

	/// 캐릭터
	// 소녀
	girl_idle, 		  // 소녀 idle
	girl_walk,		  // 소녀 walk
	girl_jump,		  // 소녀 jump
	girl_crouch,	  // 소녀 crouch
	girl_push,		  // 소녀 push

	// 그림자
	shadow_idle,	  // 그림자 idle
	shadow_walk,	  // 그림자 walk
	shadow_push,	  // 그림자 push
	shadow_jump,	  // 그림자 jump
	shadow_crouch,	  // 그림자 crouch

	// 나머지 오브젝트
	object_doll,					// 인형
	object_box,						// 박스
	object_box_shadow,				// 그림자 박스
	object_location_indication,		// 위치 표시
	object_star,					// 별 오브젝트
	object_fadeout_star,			// 별 오브젝트 페이드아웃
	object_vine,					// 덩쿨 오브젝트

	/// 플랫폼
	// 구름
	cloud1_100x40_object,
	cloud2_150x40_object,
	cloud3_250x45_object,

	// 그림자 구름
	cloud1shadow_100x40_object,
	cloud2shadow_150x40_object,
	cloud3shadow_250x45_object,

	// 바위
	rock1_75x65_object,				// 바위 1
	rock2_150x65_object,			// 바위 2
	rock3_100x215_object,			// 바위 3
	rockmix1_object,
	rockmix2_object,
	rockmix3_object,

	// 그림자 바위
	rock1shadow_75x65_object,		// 그림자 바위1
	rock2shadow_150x65_object,		// 그림자 바위2
	rock3shadow_100x215_object,		// 그림자 바위3
	rockmix1shadow_object, 
	rockmix2shadow_object,
	rockmix3shadow_object,

	/// <summary>
	/// 전에 한 거
	/// </summary>
	DEFAULT,			// 디폴트
	MONSTER,			// 몬스터
	BOX,				// 박스
	STAR,				// 별
	SHOOTING_STAR,		// 별똥별
	SAVE_POINT,			// 세이브 포인트
	THORNBUSH,          // 가시 덤불
	PLATFORM,           // 플랫폼
	LADDER,             // 사다리

	END,
};

enum class COLLIDER_LAYER
{
	PLAYER,			// 플레이어. 모든 것과 충돌감지를 한다. / 중력영향 받음 / 컨트롤 가능
	BOX,			// 박스. 모든 것과 충돌감지를 한다. / 중력의 영향 받음
	STATIC_OBJECT,	// 정적인 오브젝트. 충돌감지의 대상이다.
	GROUND,			// 지면. 충돌감지의 대상이다.
};

enum class KEY_STATE
{
	NONE,
	LEFT, 
	RIGHT, 
	JUMP,
	DOWN,
	HOLD,

	DEBUG_ALL,
	DEBUG_OBJECT,
	DEBUG_COLLISION,

};

// 씬의 종류
enum class SCENE_TYPE
{
	TITLE_SCENE,		// 타이틀씬
	START_CUT_SCENE,	// 시작 컷씬
	IN_GAME,			// 인게임
	ENDING_CUT_SCENE,	// 엔딩 컷씬
	CREDIT_SCENE		// 개발자 크레딧씬
};

// 이미지 종류 분류 스프라이트
enum class SPRITE_TYPE
{
	// 소녀 스프라이트
	PLAYER1_IDLE,		// 소녀 디폴트 상태
	PLAYER1_RUN,		// 소녀 달리기
	PLAYER1_JUMP,		// 소녀 점프
	PLAYER1_LAND,		// 소녀 점프 착지
	PLAYER1_PUSH,		// 소녀 상자 밀기
	PLAYER1_SIT,		// 소녀 앉기
	PLAYER1_STANDUP,	// 소녀 일어서기
	PLAYER1_DIE,		// 소녀 죽기

	// 그림자 스프라이트
	PLAYER2_IDLE,		// 그림자 디폴트 상태
	PLAYER2_RUN,		// 그림자 달리기
	PLAYER2_JUMP,		// 그림자 점프
	PLAYER2_LAND,		// 그림자 점프 착지
	PLAYER2_PUSH,		// 그림자 상자 밀기

	// 그외 오브젝트 스프라이트
	BOX,				// 박스
	BOX_SHADOW,			// 박스 그림자
	DOLL_IDLE,			// 인형 디폴트 상태
	PLATFORM_LAND,		// 지상 플랫폼
	PLATFORM_SKY,		// 공중 플랫폼
	THORNBUSH,			// 가시 덤불
	STAR,				// 별(체크포인트)

};

// 플레이어 상태

// 배경의 깊이에 따른 이미지 종류
enum class BACKGROUND_TYPE
{
	BACKGROUND_SKY,		// 하늘 배경
	BACKGROUND_CLOUD,   // 하늘에 있는 구름 배경
	BACKGROUND_RIVER,	// 강 배경
};

/// <summary>
/// FSM 관련
/// </summary>
enum class CHARACTER_STATE
{
	NORMAL,		// 일반 상태	(이동가능하며, 상호작용 가능)
	DIE,		// 죽음		(이동불가, 상호작용 불가)
	SIT,		// 앉은 상태	(이동불가, 상호작용 불가)

	//HOLD,		// 상자 같은 것을 잡고 미는 상태..
	//RELEASE,	// 놓는 중인 상태
	//PUSH,
};

// 캐릭터의 이동에 관련된 상태
enum class MOVE_STATE
{
	GROUND,		// 지면에 붙어 있는 상태. 바닥과의 충돌감지를 엄밀히 하지 않는다. 보정도 할 필요 없다.
	AIR,		// 공중에 뜬 상태. 중력 가속도의 영향을 받아야 한다. (ex: 마리오같은게 아니었다면 좌우 이동 불가..)

	WALLMOVE,	// 벽타기 상태. 이 게임에는 없다.
};

// 예시
//enum class CHARACTER_INTERACTION_STATE
//{
//	NORMAL,		// 일반 상태. 상호작용 없음
//	HOLD,		// 상자 같은 것을 잡고 미는 상태..
//	RELEASE,	// 놓는 중인 상태
//};


std::string ConvertState(CHARACTER_STATE state);
std::string ConvertState(MOVE_STATE state);
std::string ConvertState(PLAYER_TYPE state);


