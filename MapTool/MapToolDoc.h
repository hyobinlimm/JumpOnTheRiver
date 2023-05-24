
// MapToolDoc.h : interface of the CMapToolDoc class
//


#pragma once

#include "Action.h"
#include "ObjectInfo.h"

class CMapToolDoc : public CDocument
{
protected: // create from serialization only
	CMapToolDoc() noexcept;
	DECLARE_DYNCREATE(CMapToolDoc)

// Attributes
public:

// Operations
public:
	CArray<CPoint> m_Points;
	CList<CAction> m_Undo;
	CList<CAction> m_Redo;

	int m_ObjectIndex;
	std::vector<ObjectInfo*> m_ObjectInfos;

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMapToolDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void AddPoint(CPoint point);
	bool isUndo();
	void Undo();
	bool isRedo();
	void Redo();

	void NewData();
	void SaveData();
	void LoadData();
};
