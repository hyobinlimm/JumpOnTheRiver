#include "SpriteManager.h"
#include "DesireD2D.h"

SpriteManager::SpriteManager()
	: m_pEngine(nullptr)
{

}

SpriteManager::SpriteManager(DesireD2D* pEngine)
{
	m_pEngine = pEngine;
}

SpriteManager::~SpriteManager()
{
	m_pEngine = nullptr;
}

void SpriteManager::SpriteLoad()
{
	/// ���
	int background_sky = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ingame_sky_stars.png", 1);			// �ϴ� ���
	int background_river = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ingame_river_stars.png", 1);		// �� ���
	int background_center = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ingame_center.png", 1);			// ��� �߰� ��
	
	int background_cloud = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ingame_cloud.png", 1);					// ��� ���� 

	int background_gameTitle = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/start_screen.png", 1);		// Ÿ��Ʋ ȭ��
	int background_startCutScene1 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/start_1.png", 1);	// ���� �ƾ� 1
	int background_startCutScene2 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/start_2.png", 1);	// ���� �ƾ� 2
	int background_startCutScene3 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/start_3.png", 1);	// �� �ƾ� 3
	int background_endingCutScene1 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ending_1.png", 1);  // ���� �ƾ� 1
	int background_endingCutScene2 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ending_2.png", 1);  // ���� �ƾ� 2
	int background_endingCutScene3 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ending_3.png", 1);	// ���� �ƾ� 3
	int background_endingCredit = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/end_screen_2ENG.png", 1);	// ���� ũ����
	

	/// ĳ���� x 5
	int girl_idle = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Idle00.png", 8);			// �ҳ� idle
	int girl_walk = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Walk00.png", 8);			// �ҳ� walk
	int girl_jump = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Jump00.png", 8);			// �ҳ� jump
	int girl_crouch = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Crouch00.png", 8);		// �ҳ� crouch
	int girl_push = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Push00.png", 8);			// �ҳ� push

	// �׸��� x 5
	int shadow_idle = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Idle00.png", 8);		// �׸��� idle
	int shadow_walk = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Walk00.png", 8);		// �׸��� walk
	int shadow_push = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Push00.png", 8);		// �׸��� push

	// �׸��� jump, crouch ����
	int shadow_jump = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Jump00.png", 8);		// �׸��� jump
	int shadow_crouch = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Push00.png", 8);	// �׸��� crouch


	/// ������ ������Ʈ �ε�
	int object_doll = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/doll_object.png", 8);						// ����
	int object_box = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Box_object.png", 1);							// �ڽ�
	int object_box_shadow = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Box_shadow_object.png", 1);			// �׸��� �ڽ�
	int object_location_indication = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/location indication.png", 1); // ��ġ ǥ��
	int object_star = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/star_object.png", 8);						// �� ������Ʈ
	int object_fadeout_star = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/star_fadeout_object.png", 1);		// �� ������Ʈ ���̵�ƿ�
	int object_vine = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/vine_object.png", 1);						// ���� ������Ʈ

	/// �÷���
	// ����
	int cloud1_100x40_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud1_100x40_object.png", 1);
	int cloud2_150x40_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud2_150x40_object.png", 1);
	int cloud3_250x45_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud3_250x45_object.png", 1);

	// �׸��� ����
	int cloud1shadow_100x40_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud1shadow_100x40_object.png", 1);
	int cloud2shadow_150x40_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud2shadow_150x40_object.png", 1);
	int cloud3shadow_250x45_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud3shadow_250x45_object.png", 1);

	// ����
	int rock1_75x65_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock1_75x65_object.png", 1);
	int rock2_150x65_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock2_150x65_object.png", 1);
	int rock3_100x215_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock3_100x215_object.png", 1);
	int rockmix1_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix1_object.png", 1);
	int rockmix2_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix2_object.png", 1);
	int rockmix3_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix3_object.png", 1);

	// �׸��� ����
	int rock1shadow_75x65_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock1shadow_75x65_object.png", 1);
	int rock2shadow_150x65_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock2shadow_150x65_object.png", 1);
	int rock3shadow_100x215_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock3shadow_100x215_object.png", 1);
	int rockmix1shadow_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix1shadow_object.png", 1);
	int rockmix2shadow_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix2shadow_object.png", 1);
	int rockmix3shadow_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix3shadow_object.png", 1);
}

void SpriteManager::Release()
{

}
