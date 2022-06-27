
// MfcAnnotationDoc.cpp: CMfcAnnotationDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MfcAnnotation.h"
#endif

#include "MfcAnnotationDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMfcAnnotationDoc

IMPLEMENT_DYNCREATE(CMfcAnnotationDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcAnnotationDoc, CDocument)
	ON_COMMAND(ID_IMG_LOAD, &CMfcAnnotationDoc::OnImgLoad)
	ON_COMMAND(ID_OPTION_COLOR, &CMfcAnnotationDoc::OnOptionColor)
	ON_COMMAND(ID_THICK_1, &CMfcAnnotationDoc::OnThick1)
	ON_COMMAND(ID_THICK_3, &CMfcAnnotationDoc::OnThick3)
	ON_COMMAND(ID_THICK_5, &CMfcAnnotationDoc::OnThick5)
END_MESSAGE_MAP()


// CMfcAnnotationDoc 생성/소멸

CMfcAnnotationDoc::CMfcAnnotationDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMfcAnnotationDoc::~CMfcAnnotationDoc()
{
}

BOOL CMfcAnnotationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	m_drawType = ID_DRAW_MOUSE;
	m_drawColor = Color::Black;
	return TRUE;
}




// CMfcAnnotationDoc serialization

void CMfcAnnotationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMfcAnnotationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CMfcAnnotationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMfcAnnotationDoc::SetSearchContent(const CString& value)
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

// CMfcAnnotationDoc 진단

#ifdef _DEBUG
void CMfcAnnotationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcAnnotationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMfcAnnotationDoc 명령


void CMfcAnnotationDoc::OnImgLoad()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	TCHAR szFilter[] = _T("Image(*.png, *.gif, *.jpg)|*.png;*.gif;*.jpg|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal()) {
		m_ImgPath = dlg.GetPathName();
		AfxMessageBox(m_ImgPath);
		matImg = imread(string(CT2CA(m_ImgPath)));
	}

	UpdateAllViews(NULL);
}


void CMfcAnnotationDoc::OnOptionColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlg;

	if (dlg.DoModal() == IDOK) {
		m_drawColor.SetFromCOLORREF(dlg.GetColor());
	}
}


void CMfcAnnotationDoc::OnThick1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_drawThick = 1;
}


void CMfcAnnotationDoc::OnThick3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_drawThick = 3;
}


void CMfcAnnotationDoc::OnThick5()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_drawThick = 20;
}
