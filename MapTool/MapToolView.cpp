
// MapToolView.cpp : implementation of the CMapToolView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MapTool.h"
#include "MapToolDoc.h"
#include "MapToolView.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapToolView

IMPLEMENT_DYNCREATE(CMapToolView, CFormView)

BEGIN_MESSAGE_MAP(CMapToolView, CFormView)

END_MESSAGE_MAP()

// CMapToolView construction/destruction

CMapToolView::CMapToolView() noexcept
	: CFormView(IDD_MAPTOOL_FORM)
{
	// TODO: add construction code here
}

CMapToolView::~CMapToolView()
{
}

void CMapToolView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMapToolView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMapToolView diagnostics

#ifdef _DEBUG
void CMapToolView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMapToolView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMapToolDoc* CMapToolView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolDoc)));
	return (CMapToolDoc*)m_pDocument;
}
#endif //_DEBUG
