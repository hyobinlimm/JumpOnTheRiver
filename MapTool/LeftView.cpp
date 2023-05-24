// LeftView.cpp : implementation file
//

#include "pch.h"
#include "MapTool.h"
#include "MainFrm.h"
#include "MapToolDoc.h"
#include "LeftView.h"
#include "RightView.h"
#include "Action.h"
#include "ObjectInfo.h"


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(IDD_FORMVIEW)
{	
}

CLeftView::~CLeftView()
{
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_OBJECT, m_ObjectName);
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_OBJECT, &CLeftView::OnCbnSelchangeComboObject)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CLeftView::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CLeftView::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CLeftView::OnBnClickedButtonNew)
END_MESSAGE_MAP()


// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView message handlers


void CLeftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();

	((CComboBox*)GetDlgItem(IDC_COMBO_OBJECT))->SetCurSel(0);
	SetObjectIndex(0);
	pDoc->m_ObjectIndex = GetObjectIndex();

	UpdateData(FALSE);
}


void CLeftView::OnCbnSelchangeComboObject()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();

	if (m_ObjectName == _T("Cloud1"))
	{
		SetObjectIndex(0);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Cloud1_Shadow"))
	{
		SetObjectIndex(1);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Cloud2"))
	{
		SetObjectIndex(2);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Cloud2_Shadow"))
	{
		SetObjectIndex(3);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Cloud3"))
	{
		SetObjectIndex(4);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Cloud3_Shadow"))
	{
		SetObjectIndex(5);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock1"))
	{
		SetObjectIndex(6);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock1_Shadow"))
	{
		SetObjectIndex(7);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock2"))
	{
		SetObjectIndex(8);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock2_Shadow"))
	{
		SetObjectIndex(9);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock3"))
	{
		SetObjectIndex(10);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock3_Shadow"))
	{
		SetObjectIndex(11);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock4"))
	{
		SetObjectIndex(12);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock4_Shadow"))
	{
		SetObjectIndex(13);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock5"))
	{
		SetObjectIndex(14);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock5_Shadow"))
	{
		SetObjectIndex(15);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock6"))
	{
		SetObjectIndex(16);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Rock6_Shadow"))
	{
		SetObjectIndex(17);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Box"))
	{
		SetObjectIndex(18);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Box_Shadow"))
	{
		SetObjectIndex(19);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Vine"))
	{
		SetObjectIndex(20);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Doll"))
	{
		SetObjectIndex(21);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}
	else if (m_ObjectName == _T("Star"))
	{
		SetObjectIndex(22);
		pDoc->m_ObjectIndex = GetObjectIndex();
	}

	UpdateData(FALSE);
}

int CLeftView::GetObjectIndex()
{
	return m_ObjectIndex;
}

void CLeftView::SetObjectIndex(int index)
{
	m_ObjectIndex = index;
}

void CLeftView::OnBnClickedButtonNew()
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();
	CRightView* pRightView = pFrame->GetRightView();

	if (IDOK == MessageBox(_T("Open a new window?"), NULL, MB_OKCANCEL | MB_ICONQUESTION))
	{
		// 데이터를 새로 만듭니다.
		pDoc->NewData();

		// 오른쪽 화면을 갱신합니다.
		pRightView->Invalidate(FALSE);
	}
}

void CLeftView::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();
	CRightView* pRightView = pFrame->GetRightView();

	if (IDOK == MessageBox(_T("Save the data?"), NULL, MB_OKCANCEL | MB_ICONQUESTION))
	{
		// 데이터를 저장합니다.
		pDoc->SaveData();
	}
}

void CLeftView::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();
	CRightView* pRightView = pFrame->GetRightView();

	if (IDOK == MessageBox(_T("Load the data?"), NULL, MB_OKCANCEL | MB_ICONQUESTION))
	{
		// 데이터를 로드합니다.
		pDoc->LoadData();

		// 오른쪽 화면을 갱신합니다.
		pRightView->Invalidate(FALSE);
	}
}
