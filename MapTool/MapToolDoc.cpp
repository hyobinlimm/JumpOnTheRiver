
// MapToolDoc.cpp : implementation of the CMapToolDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MapTool.h"
#endif

#include "MainFrm.h"
#include "MapToolDoc.h"
#include "LeftView.h"
#include "RightView.h"
#include "ObjectInfo.h"

#include <propkey.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMapToolDoc

IMPLEMENT_DYNCREATE(CMapToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapToolDoc, CDocument)
END_MESSAGE_MAP()


// CMapToolDoc construction/destruction

CMapToolDoc::CMapToolDoc() noexcept
{
	// TODO: add one-time construction code here
	m_ObjectInfos.clear();
}

CMapToolDoc::~CMapToolDoc()
{
	for (size_t i = 0; i < m_ObjectInfos.size(); i++)
	{
		delete m_ObjectInfos[i];
	}

	m_ObjectInfos.clear();
}

BOOL CMapToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMapToolDoc serialization

void CMapToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMapToolDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMapToolDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMapToolDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMapToolDoc diagnostics

#ifdef _DEBUG
void CMapToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMapToolDoc commands


void CMapToolDoc::AddPoint(CPoint point)
{
	// Record action for undo
	CAction action;

	action.m_Action = CAction::Add;
	action.m_Info = (int)m_Points.Add(point);
	action.m_Point = point;

	m_Undo.AddHead(action);

	while (m_Undo.GetCount() > MAX_UNDO)
	{
		m_Undo.RemoveTail();
	}

	// Redo sequence
	m_Redo.RemoveAll();

	UpdateAllViews(NULL);
}


bool CMapToolDoc::isUndo()
{
	return (m_Undo.GetCount() > 0);
}


void CMapToolDoc::Undo()
{
	CAction action = m_Undo.RemoveHead();

	switch (action.m_Action)
	{
	case CAction::Add:
		m_Points.RemoveAt(action.m_Info);
		m_Redo.AddHead(action);

		while (m_Redo.GetCount() > MAX_UNDO)
		{
			m_Redo.RemoveTail();
		}

		break;
	}

	UpdateAllViews(NULL);
}


bool CMapToolDoc::isRedo()
{
	return (m_Redo.GetCount() > 0);
}


void CMapToolDoc::Redo()
{
	CAction action = m_Redo.RemoveHead();

	switch (action.m_Action)
	{
	case CAction::Add:
		m_Points.Add(action.m_Point);
		m_Undo.AddHead(action);

		while (m_Undo.GetCount() > MAX_UNDO)

			m_Undo.RemoveTail();

		break;
	}

	UpdateAllViews(NULL);
}


void CMapToolDoc::SaveData()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();

	rapidjson::GenericDocument< rapidjson::UTF16<> > Json;
	Json.SetObject();

	rapidjson::GenericValue< rapidjson::UTF16<> > key, value;

	key.SetString(_T("Object"));

	value.SetObject();
	rapidjson::GenericValue< rapidjson::UTF16<> > Key_1, value_1;

	key.SetString(_T("Info"));
	value.SetArray();

	for (size_t i = 0; i < pDoc->m_ObjectInfos.size(); i++)
	{
		ObjectInfo* pObjectInfo = pDoc->m_ObjectInfos[i];
		int index = pObjectInfo->index;
		int x = pObjectInfo->x;
		int y = pObjectInfo->y;

		rapidjson::GenericValue< rapidjson::UTF16<> > Key_2, value_2;
		Key_2.SetString(_T("No."));
		value_2.SetObject();
		value_2.AddMember(Key_2, value_1.SetInt(i), Json.GetAllocator());
		value_2.AddMember(Key_2.SetString(_T("Index")), value_1.SetInt(index), Json.GetAllocator());
		value_2.AddMember(Key_2.SetString(_T("X")), value_1.SetInt(x), Json.GetAllocator());
		value_2.AddMember(Key_2.SetString(_T("Y")), value_1.SetInt(y), Json.GetAllocator());
		value.PushBack(value_2, Json.GetAllocator());
	}

	Json.AddMember(key, value, Json.GetAllocator());

	rapidjson::GenericStringBuffer< rapidjson::UTF16<> > strbuf;
	rapidjson::Writer< rapidjson::GenericStringBuffer< rapidjson::UTF16<> >, rapidjson::UTF16<>, rapidjson::UTF16<> > writer(strbuf);
	Json.Accept(writer);

	HANDLE hFile = CreateFile(_T("Map.json"), GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE != hFile)
	{
		DWORD dwWrite = 0;

		WORD wUnicode16LEHeader = 0xFEFF;
		WriteFile(hFile, &wUnicode16LEHeader, sizeof(wUnicode16LEHeader), &dwWrite, nullptr);
		WriteFile(hFile, strbuf.GetString(), strbuf.GetSize(), &dwWrite, nullptr);

		CloseHandle(hFile);
	}
}

void CMapToolDoc::NewData()
{
	// 기존 데이터를 삭제합니다.
	m_Points.RemoveAll();
	m_ObjectInfos.clear();
}

void CMapToolDoc::LoadData()
{
	// 기존 데이터를 삭제합니다.
	m_Points.RemoveAll();
	m_ObjectInfos.clear();

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMapToolDoc* pDoc = (CMapToolDoc*)pFrame->GetActiveDocument();

	rapidjson::GenericDocument<rapidjson::UTF16<>> Json;

	FILE* fp = nullptr;
	fopen_s(&fp, "Map.json", "rb");

	if (fp != nullptr)
	{
		fseek(fp, 0, SEEK_END);
		int nFileSize = ftell(fp);

		fseek(fp, 2, SEEK_SET);

		wchar_t* str = new wchar_t[nFileSize]();

		int size = sizeof(wchar_t);
		fread(str, size, nFileSize, fp);
		Json.Parse(str);

		delete[] str;
		fclose(fp);
	}
	else
	{
		return;
	}

	rapidjson::GenericValue< rapidjson::UTF16<>>& infoArray = Json[_T("Info")].GetArray();


	// m_ObjectInfo에 데이터를 저장합니다.
	ObjectInfo* pObjectInfo = nullptr;

	for (size_t i = 0; i < infoArray.Size(); i++)
	{
		pObjectInfo = new ObjectInfo();
		pObjectInfo->index = infoArray[i][_T("Index")].GetInt();
		pObjectInfo->x = infoArray[i][_T("X")].GetInt();
		pObjectInfo->y = infoArray[i][_T("Y")].GetInt();

		m_ObjectInfos.push_back(pObjectInfo);
	}
}
