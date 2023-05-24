#pragma once
#include <string>

/// <summary>
/// ���� ������ ���̴� ��� ���� (���, �ʱ갪 ��)
/// 
/// 2022.02.21 LeHideHome
/// </summary>

// ������Ʈ���� �ʱ� ��ġ

/// <summary>
/// ����� ����ϱ� ���� Ŭ����. static const�� ����Ѵ�.
/// </summary>
class ConstValue
{
public:
	static const int StartPosX = 104;

	static const int PositiveY = 500-55;	// ������ ����
	static const int GroundY = 540;			// �������� ���� (���ǰ� �׸����� �߰�)
	static const int NegativeY = 580+55;	// �׸����� ����
};


// player �̵����ѿ�
#define MIN_X 30
#define MAX_X 5700
#define MINOFFSET_X 26
#define MAXOFFSET_X 5704

// ������
#define GROUNDYPOS 400
#define GRAVITY 50.0f
#define JUMP_POWER 15.0f

// ī�޶��
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

// ����Ű���� ���� (16������ �ٲ� ��)
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

// ���� ������ ������Ʈ�� �з��� �ߴ�!
// �÷��̾�� ������Ʈ�� �ٸ� ENUM CLASS�� ���� �־���� �� ����. 

enum class PLAYER_TYPE
{
	GIRL,			// �ҳ�
	SHADOW,			// �׸���
};

enum class OBJECT_TYPE
{
	/// ���
	background_sky,				   // �ϴ� ���
	background_river,			   // �� ���
	background_center,			   // ��� �߰� ��
	
	background_cloud,				// ��� ���� 

	background_gameTitle,			   // Ÿ��Ʋ ȭ��
	background_startCutScene1,		   // ���� �ƾ� 1
	background_startCutScene2,		   // ���� �ƾ� 2
	background_startCutScene3,	       // ���� �ƾ� 3
	background_endingCutScene1,		   // ���� �ƾ� 1
	background_endingCutScene2,		   // ���� �ƾ� 2
	background_endingCutScene3,		   // ���� �ƾ� 3
	background_endingCredit,		   // ���� ũ����

	/// ĳ����
	// �ҳ�
	girl_idle, 		  // �ҳ� idle
	girl_walk,		  // �ҳ� walk
	girl_jump,		  // �ҳ� jump
	girl_crouch,	  // �ҳ� crouch
	girl_push,		  // �ҳ� push

	// �׸���
	shadow_idle,	  // �׸��� idle
	shadow_walk,	  // �׸��� walk
	shadow_push,	  // �׸��� push
	shadow_jump,	  // �׸��� jump
	shadow_crouch,	  // �׸��� crouch

	// ������ ������Ʈ
	object_doll,					// ����
	object_box,						// �ڽ�
	object_box_shadow,				// �׸��� �ڽ�
	object_location_indication,		// ��ġ ǥ��
	object_star,					// �� ������Ʈ
	object_fadeout_star,			// �� ������Ʈ ���̵�ƿ�
	object_vine,					// ���� ������Ʈ

	/// �÷���
	// ����
	cloud1_100x40_object,
	cloud2_150x40_object,
	cloud3_250x45_object,

	// �׸��� ����
	cloud1shadow_100x40_object,
	cloud2shadow_150x40_object,
	cloud3shadow_250x45_object,

	// ����
	rock1_75x65_object,				// ���� 1
	rock2_150x65_object,			// ���� 2
	rock3_100x215_object,			// ���� 3
	rockmix1_object,
	rockmix2_object,
	rockmix3_object,

	// �׸��� ����
	rock1shadow_75x65_object,		// �׸��� ����1
	rock2shadow_150x65_object,		// �׸��� ����2
	rock3shadow_100x215_object,		// �׸��� ����3
	rockmix1shadow_object, 
	rockmix2shadow_object,
	rockmix3shadow_object,

	/// <summary>
	/// ���� �� ��
	/// </summary>
	DEFAULT,			// ����Ʈ
	MONSTER,			// ����
	BOX,				// �ڽ�
	STAR,				// ��
	SHOOTING_STAR,		// ���˺�
	SAVE_POINT,			// ���̺� ����Ʈ
	THORNBUSH,          // ���� ����
	PLATFORM,           // �÷���
	LADDER,             // ��ٸ�

	END,
};

enum class COLLIDER_LAYER
{
	PLAYER,			// �÷��̾�. ��� �Ͱ� �浹������ �Ѵ�. / �߷¿��� ���� / ��Ʈ�� ����
	BOX,			// �ڽ�. ��� �Ͱ� �浹������ �Ѵ�. / �߷��� ���� ����
	STATIC_OBJECT,	// ������ ������Ʈ. �浹������ ����̴�.
	GROUND,			// ����. �浹������ ����̴�.
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

// ���� ����
enum class SCENE_TYPE
{
	TITLE_SCENE,		// Ÿ��Ʋ��
	START_CUT_SCENE,	// ���� �ƾ�
	IN_GAME,			// �ΰ���
	ENDING_CUT_SCENE,	// ���� �ƾ�
	CREDIT_SCENE		// ������ ũ������
};

// �̹��� ���� �з� ��������Ʈ
enum class SPRITE_TYPE
{
	// �ҳ� ��������Ʈ
	PLAYER1_IDLE,		// �ҳ� ����Ʈ ����
	PLAYER1_RUN,		// �ҳ� �޸���
	PLAYER1_JUMP,		// �ҳ� ����
	PLAYER1_LAND,		// �ҳ� ���� ����
	PLAYER1_PUSH,		// �ҳ� ���� �б�
	PLAYER1_SIT,		// �ҳ� �ɱ�
	PLAYER1_STANDUP,	// �ҳ� �Ͼ��
	PLAYER1_DIE,		// �ҳ� �ױ�

	// �׸��� ��������Ʈ
	PLAYER2_IDLE,		// �׸��� ����Ʈ ����
	PLAYER2_RUN,		// �׸��� �޸���
	PLAYER2_JUMP,		// �׸��� ����
	PLAYER2_LAND,		// �׸��� ���� ����
	PLAYER2_PUSH,		// �׸��� ���� �б�

	// �׿� ������Ʈ ��������Ʈ
	BOX,				// �ڽ�
	BOX_SHADOW,			// �ڽ� �׸���
	DOLL_IDLE,			// ���� ����Ʈ ����
	PLATFORM_LAND,		// ���� �÷���
	PLATFORM_SKY,		// ���� �÷���
	THORNBUSH,			// ���� ����
	STAR,				// ��(üũ����Ʈ)

};

// �÷��̾� ����

// ����� ���̿� ���� �̹��� ����
enum class BACKGROUND_TYPE
{
	BACKGROUND_SKY,		// �ϴ� ���
	BACKGROUND_CLOUD,   // �ϴÿ� �ִ� ���� ���
	BACKGROUND_RIVER,	// �� ���
};

/// <summary>
/// FSM ����
/// </summary>
enum class CHARACTER_STATE
{
	NORMAL,		// �Ϲ� ����	(�̵������ϸ�, ��ȣ�ۿ� ����)
	DIE,		// ����		(�̵��Ұ�, ��ȣ�ۿ� �Ұ�)
	SIT,		// ���� ����	(�̵��Ұ�, ��ȣ�ۿ� �Ұ�)

	//HOLD,		// ���� ���� ���� ��� �̴� ����..
	//RELEASE,	// ���� ���� ����
	//PUSH,
};

// ĳ������ �̵��� ���õ� ����
enum class MOVE_STATE
{
	GROUND,		// ���鿡 �پ� �ִ� ����. �ٴڰ��� �浹������ ������ ���� �ʴ´�. ������ �� �ʿ� ����.
	AIR,		// ���߿� �� ����. �߷� ���ӵ��� ������ �޾ƾ� �Ѵ�. (ex: ������������ �ƴϾ��ٸ� �¿� �̵� �Ұ�..)

	WALLMOVE,	// ��Ÿ�� ����. �� ���ӿ��� ����.
};

// ����
//enum class CHARACTER_INTERACTION_STATE
//{
//	NORMAL,		// �Ϲ� ����. ��ȣ�ۿ� ����
//	HOLD,		// ���� ���� ���� ��� �̴� ����..
//	RELEASE,	// ���� ���� ����
//};


std::string ConvertState(CHARACTER_STATE state);
std::string ConvertState(MOVE_STATE state);
std::string ConvertState(PLAYER_TYPE state);


