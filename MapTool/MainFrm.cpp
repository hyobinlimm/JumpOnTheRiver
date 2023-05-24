
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "MapTool.h"
#include "MapToolDoc.h"
#include "LeftView.h"
#include "RightView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Delete these three lines if you don't want the toolbar to be dockable

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// ȭ���� ��, ��� �����մϴ�.
	m_wndSplitter.CreateStatic(this, 1, 2);

	// ���� ȭ�鿡 CLeftView�� �����մϴ�.
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(0, 0), pContext);

	// ���� ȭ�鿡 CRightView�� �����մϴ�.
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(0, 0), pContext);

	// �� View���� ������ �����Դϴ�.
	m_pLeftView = static_cast<CLeftView*>(m_wndSplitter.GetPane(0, 0));
	m_pRightView = static_cast<CRightView*>(m_wndSplitter.GetPane(0, 1));

	// ȭ���� �����ϴ� ���ؼ��� ��ġ�Դϴ�.
	m_wndSplitter.SetColumnInfo(0, SPLIT_POSITION, 0);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;
	cs.x = 0;
	cs.y = 0;

	CMenu* pMenu = new CMenu;
	pMenu->Attach(cs.hMenu);
	pMenu->DestroyMenu();
	cs.hMenu = NULL;
	delete pMenu; pMenu = NULL;

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

