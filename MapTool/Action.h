#pragma once

// 사용자의 행동에 따라서 오브젝트를 추가, 삭제하는 클래스입니다.
class CAction
{
public:
	enum Actions
	{
		Add,
		Delete,
		Move
	};

	CAction()
	{
	}

	~CAction()
	{
	}

	CAction(CAction& action)
	{
		m_Action = action.m_Action;
		m_Info = action.m_Info;
		m_Point = action.m_Point;
	}

	int m_Action;
	int m_Info;
	CPoint m_Point;
};
