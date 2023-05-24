#pragma once

// ������� �ൿ�� ���� ������Ʈ�� �߰�, �����ϴ� Ŭ�����Դϴ�.
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
