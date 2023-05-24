#include "OutroCredit.h"
#include "DesireD2D.h"
#include <windows.h>

class DesireD2D;

OutroCredit::OutroCredit()
{
}

OutroCredit::~OutroCredit()
{
}

void OutroCredit::Initialize()
{
	m_ID = OBJECT_TYPE::background_endingCredit;
}

void OutroCredit::Update()
{
	
}

void OutroCredit::Draw()
{
	S_pSceneManager->m_pEngine2D->DrawSprite((int)m_ID, 0, 960, 540);
}

void OutroCredit::Release()
{
}
