// RightView.cpp : implementation file
//

#include "pch.h"
#include "MainFrm.h"
#include "MapTool.h"
#include "MapToolDoc.h"
#include "LeftView.h"
#include "RightView.h"


// CRightView

IMPLEMENT_DYNCREATE(CRightView, CScrollView)


CRightView::CRightView()
{
}

CRightView::~CRightView()
{
}


BEGIN_MESSAGE_MAP(CRightView, CScrollView)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CRightView drawing

void CRightView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: calculate the total size of this view
	CRect rc;
	GetClientRect(&rc);
	CSize sizeViewPage;

	sizeViewPage.cx = RESOLUTION_X;
	sizeViewPage.cy = RESOLUTION_Y;

	CSize sizeViewPageTotal;
	sizeViewPageTotal.cx = sizeViewPage.cx;
	sizeViewPageTotal.cy = sizeViewPage.cy;

	m_Background.Load(_T(".\\res\\Background.png"));
	m_Cloud1.Load(_T(".\\res\\Cloud1.png"));
	m_Cloud1_Shadow.Load(_T(".\\res\\Cloud1_Shadow.png"));
	m_Cloud2.Load(_T(".\\res\\Cloud2.png"));
	m_Cloud2_Shadow.Load(_T(".\\res\\Cloud2_Shadow.png"));
	m_Cloud3.Load(_T(".\\res\\Cloud3.png"));
	m_Cloud3_Shadow.Load(_T(".\\res\\Cloud3_Shadow.png"));
	m_Rock1.Load(_T(".\\res\\Rock1.png"));
	m_Rock1_Shadow.Load(_T(".\\res\\Rock1_Shadow.png"));
	m_Rock2.Load(_T(".\\res\\Rock2.png"));
	m_Rock2_Shadow.Load(_T(".\\res\\Rock2_Shadow.png"));
	m_Rock3.Load(_T(".\\res\\Rock3.png"));
	m_Rock3_Shadow.Load(_T(".\\res\\Rock3_Shadow.png"));
	m_Rock4.Load(_T(".\\res\\Rock4.png"));
	m_Rock4_Shadow.Load(_T(".\\res\\Rock4_Shadow.png"));
	m_Rock5.Load(_T(".\\res\\Rock5.png"));
	m_Rock5_Shadow.Load(_T(".\\res\\Rock5_Shadow.png"));
	m_Rock6.Load(_T(".\\res\\Rock6.png"));
	m_Rock6_Shadow.Load(_T(".\\res\\Rock6_Shadow.png"));
	m_Box.Load(_T(".\\res\\Box.png"));
	m_Box_Shadow.Load(_T(".\\res\\Box_Shadow.png"));
	m_Vine.Load(_T(".\\res\\Vine.png"));
	m_Doll.Load(_T(".\\res\\Doll.png"));
	m_Star.Load(_T(".\\res\\Star.png"));

	m_pObjectImages.push_back(&m_Cloud1);
	m_pObjectImages.push_back(&m_Cloud1_Shadow);
	m_pObjectImages.push_back(&m_Cloud2);
	m_pObjectImages.push_back(&m_Cloud2_Shadow);
	m_pObjectImages.push_back(&m_Cloud3);
	m_pObjectImages.push_back(&m_Cloud3_Shadow);
	m_pObjectImages.push_back(&m_Rock1);
	m_pObjectImages.push_back(&m_Rock1_Shadow);
	m_pObjectImages.push_back(&m_Rock2);
	m_pObjectImages.push_back(&m_Rock2_Shadow);
	m_pObjectImages.push_back(&m_Rock3);
	m_pObjectImages.push_back(&m_Rock3_Shadow);
	m_pObjectImages.push_back(&m_Rock4);
	m_pObjectImages.push_back(&m_Rock4_Shadow);
	m_pObjectImages.push_back(&m_Rock5);
	m_pObjectImages.push_back(&m_Rock5_Shadow);
	m_pObjectImages.push_back(&m_Rock6);
	m_pObjectImages.push_back(&m_Rock6_Shadow);
	m_pObjectImages.push_back(&m_Box);
	m_pObjectImages.push_back(&m_Box_Shadow);
	m_pObjectImages.push_back(&m_Vine);
	m_pObjectImages.push_back(&m_Doll);
	m_pObjectImages.push_back(&m_Star);

	SetScrollSizes(MM_TEXT, sizeViewPageTotal);
}


// CRightView diagnostics

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CScrollView::AssertValid();
}

CMapToolDoc* CRightView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolDoc)));
	return (CMapToolDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _DEBUG
inline CMapToolDoc* CRightView::GetDocument() const
{
	return (CMapToolDoc*)m_pDocument;
}
#endif


// CRightView message handlers


void CRightView::OnDraw(CDC* pDC)
{
	CMapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code here
}

void CRightView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CScrollView::OnPaint() for painting messages

	OnPrepareDC(&dc);

	CMapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc)
	{
		return;
	}

	// 화면의 크기를 구합니다.
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// 임시 버퍼를 생성합니다.
	memDC.CreateCompatibleDC(&dc);

	// 비트맵을 생성합니다.
	bitmap.CreateCompatibleBitmap(&dc, m_Background.GetWidth(), m_Background.GetHeight());

	// 이전 비트맵울 보존합니다.
	pOldBitmap = memDC.SelectObject(&bitmap);

	// 임시 버퍼를 검정색으로 채웁니다.
	memDC.PatBlt(0, 0, m_Background.GetWidth(), m_Background.GetHeight(), BLACKNESS);

	// 임시 버퍼에 이미지를 그립니다.
	if (m_Background != NULL)
	{
		m_Background.BitBlt(memDC, 0, 0, SRCCOPY);

		if (pDoc->m_ObjectInfos.size() != 0)
		{
			for (size_t i = 0; i < pDoc->m_ObjectInfos.size(); i++)
			{
				ObjectInfo* pObjectInfo = pDoc->m_ObjectInfos[i];

				this->DrawObjectImage(pObjectInfo, m_pObjectImages[pObjectInfo->index], &memDC);
			}
		}
	}
	else
	{
		return;
	}

	// 임시 버퍼를 DC에 그립니다.
	dc.BitBlt(0, 0, m_Background.GetWidth(), m_Background.GetHeight(), &memDC, 0, 0, SRCCOPY);

	// 이전 비트맵으로 재설정합니다.
	memDC.SelectObject(pOldBitmap);

	// 생성한 리소스 해제합니다.
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


void CRightView::SetScrollSize()
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CSize sizeTotal(m_Background.GetWidth(), m_Background.GetHeight());

	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CRightView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();

	ObjectInfo* pObjectInfo = new ObjectInfo();

	if (pDoc->m_Points.GetCount() <= MAX_UNDO)
	{
		pDoc->AddPoint(point + GetScrollPosition());

		pObjectInfo->index = pDoc->m_ObjectIndex;
		pObjectInfo->x = point.x + GetScrollPosition().x;
		pObjectInfo->y = point.y + GetScrollPosition().y;

		pDoc->m_ObjectInfos.push_back(pObjectInfo);
	}

	CScrollView::OnLButtonDown(nFlags, point);
}

void CRightView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();

	if (pDoc->m_Points.GetCount() != NULL)
	{
		pDoc->Undo();
		pDoc->m_ObjectInfos.pop_back();
	}

	CScrollView::OnRButtonDown(nFlags, point);
}

void CRightView::DrawObjectImage(ObjectInfo* pObjectInfo, CImage* pImage, CDC* pDC)
{
	pImage->Draw(*pDC, pObjectInfo->x - pImage->GetWidth() / HALF, pObjectInfo->y - pImage->GetHeight() / HALF);

	CString strPoint;
	strPoint.Format(_T("%04d, %04d"), pObjectInfo->x, pObjectInfo->y);
	pDC->TextOut(pObjectInfo->x - pImage->GetWidth() / HALF, pObjectInfo->y - pImage->GetHeight() / HALF, strPoint);
}