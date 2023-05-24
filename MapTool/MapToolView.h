
// MapToolView.h : interface of the CMapToolView class
//

#pragma once


class CMapToolView : public CFormView
{
protected: // create from serialization only
	CMapToolView() noexcept;
	DECLARE_DYNCREATE(CMapToolView)

public:

#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MAPTOOL_FORM };
#endif

// Attributes
public:
	CMapToolDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // debug version in MapToolView.cpp
inline CMapToolDoc* CMapToolView::GetDocument() const
   { return reinterpret_cast<CMapToolDoc*>(m_pDocument); }
#endif

