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
	/// 배경
	int background_sky = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ingame_sky_stars.png", 1);			// 하늘 배경
	int background_river = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ingame_river_stars.png", 1);		// 강 배경
	int background_center = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ingame_center.png", 1);			// 배경 중간 선
	
	int background_cloud = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ingame_cloud.png", 1);					// 배경 구름 

	int background_gameTitle = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/start_screen.png", 1);		// 타이틀 화면
	int background_startCutScene1 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/start_1.png", 1);	// 시작 컷씬 1
	int background_startCutScene2 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/start_2.png", 1);	// 시작 컷씬 2
	int background_startCutScene3 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/start_3.png", 1);	// 작 컷씬 3
	int background_endingCutScene1 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ending_1.png", 1);  // 엔딩 컷씬 1
	int background_endingCutScene2 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ending_2.png", 1);  // 엔딩 컷씬 2
	int background_endingCutScene3 = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/ending_3.png", 1);	// 엔딩 컷씬 3
	int background_endingCredit = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/end_screen_2ENG.png", 1);	// 엔딩 크레딧
	

	/// 캐릭터 x 5
	int girl_idle = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Idle00.png", 8);			// 소녀 idle
	int girl_walk = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Walk00.png", 8);			// 소녀 walk
	int girl_jump = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Jump00.png", 8);			// 소녀 jump
	int girl_crouch = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Crouch00.png", 8);		// 소녀 crouch
	int girl_push = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Girl_Push00.png", 8);			// 소녀 push

	// 그림자 x 5
	int shadow_idle = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Idle00.png", 8);		// 그림자 idle
	int shadow_walk = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Walk00.png", 8);		// 그림자 walk
	int shadow_push = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Push00.png", 8);		// 그림자 push

	// 그림자 jump, crouch 없음
	int shadow_jump = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Jump00.png", 8);		// 그림자 jump
	int shadow_crouch = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Shadow_Push00.png", 8);	// 그림자 crouch


	/// 나머지 오브젝트 로드
	int object_doll = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/doll_object.png", 8);						// 인형
	int object_box = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Box_object.png", 1);							// 박스
	int object_box_shadow = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/Box_shadow_object.png", 1);			// 그림자 박스
	int object_location_indication = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/location indication.png", 1); // 위치 표시
	int object_star = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/star_object.png", 8);						// 별 오브젝트
	int object_fadeout_star = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/star_fadeout_object.png", 1);		// 별 오브젝트 페이드아웃
	int object_vine = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/vine_object.png", 1);						// 덩쿨 오브젝트

	/// 플랫폼
	// 구름
	int cloud1_100x40_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud1_100x40_object.png", 1);
	int cloud2_150x40_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud2_150x40_object.png", 1);
	int cloud3_250x45_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud3_250x45_object.png", 1);

	// 그림자 구름
	int cloud1shadow_100x40_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud1shadow_100x40_object.png", 1);
	int cloud2shadow_150x40_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud2shadow_150x40_object.png", 1);
	int cloud3shadow_250x45_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/cloud3shadow_250x45_object.png", 1);

	// 바위
	int rock1_75x65_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock1_75x65_object.png", 1);
	int rock2_150x65_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock2_150x65_object.png", 1);
	int rock3_100x215_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rock3_100x215_object.png", 1);
	int rockmix1_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix1_object.png", 1);
	int rockmix2_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix2_object.png", 1);
	int rockmix3_object = m_pEngine->LoadSpriteSheet("../JumpOnTheRiver/Data/platform/rockmix3_object.png", 1);

	// 그림자 바위
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
