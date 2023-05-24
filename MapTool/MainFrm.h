
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

class MapToolDoc;
class CLeftView;
class CRightView;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
private:
	CLeftView* m_pLeftView;
	CRightView* m_pRightView;
protected:
	CSplitterWnd m_wndSplitter;
public:
	CLeftView* GetLeftView() const
	{
		return m_pLeftView;
	}
	CRightView* GetRightView() const
	{
		return m_pRightView;
	}

// Operations
public:

// Overrides
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	//CToolBar          m_wndToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


