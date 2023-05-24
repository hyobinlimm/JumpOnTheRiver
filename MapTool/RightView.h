#pragma once


// CRightView view

class CMapToolDoc;
struct ObjectInfo;

class CRightView : public CScrollView
{
	DECLARE_DYNCREATE(CRightView)

public:
	CImage m_Background;
	CImage m_Cloud1;
	CImage m_Cloud1_Shadow;
	CImage m_Cloud2;
	CImage m_Cloud2_Shadow;
	CImage m_Cloud3;
	CImage m_Cloud3_Shadow;
	CImage m_Rock1;
	CImage m_Rock1_Shadow;
	CImage m_Rock2;
	CImage m_Rock2_Shadow;
	CImage m_Rock3;
	CImage m_Rock3_Shadow;
	CImage m_Rock4;
	CImage m_Rock4_Shadow;
	CImage m_Rock5;
	CImage m_Rock5_Shadow;
	CImage m_Rock6;
	CImage m_Rock6_Shadow;
	CImage m_Box;
	CImage m_Box_Shadow;
	CImage m_Vine;
	CImage m_Doll;
	CImage m_Star;

	std::vector<CImage*> m_pObjectImages;

private:
	void DrawObjectImage(ObjectInfo* pObjectInfo, CImage* pImage, CDC* pDC);

protected:
	CRightView();           // protected constructor used by dynamic creation
	virtual ~CRightView();

public:
	CMapToolDoc* GetDocument() const;

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	void SetScrollSize();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
