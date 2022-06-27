
// MfcAnnotationView.cpp: CMfcAnnotationView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MfcAnnotation.h"
#endif

//#include "MfcAnnotationDoc.h"
#include "MfcAnnotationView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcAnnotationView

IMPLEMENT_DYNCREATE(CMfcAnnotationView, CView)

BEGIN_MESSAGE_MAP(CMfcAnnotationView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND_RANGE(ID_DRAW_RECTANGLE, ID_DRAW_STRING, OnChangeTool)
	ON_UPDATE_COMMAND_UI_RANGE(ID_DRAW_RECTANGLE, ID_DRAW_STRING, OnUpdateChangeTool)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_STRING, &CMfcAnnotationView::OnDrawString)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMfcAnnotationView 생성/소멸

CMfcAnnotationView::CMfcAnnotationView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMfcAnnotationView::~CMfcAnnotationView()
{
}

BOOL CMfcAnnotationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMfcAnnotationView 그리기

void CMfcAnnotationView::OnDraw(CDC* pDC)
{
	CMfcAnnotationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rectDraw;		// 사각형 도화지 준비
	GetClientRect(rectDraw);	// 도화지 선언
	memBit = make_shared<Bitmap>(rectDraw.Width(), rectDraw.Height());
	Graphics memDC(memBit.get());	// 메모리bitmap

	//Img load
	Graphics g(pDC->m_hDC);
	if (!(pDoc->matImg.empty())) {
		cvtColor(pDoc->matImg, pDoc->matImg, COLOR_BGR2BGRA);

		Bitmap bitmap((INT)pDoc->matImg.size().width, (INT)pDoc->matImg.size().height, (INT)pDoc->matImg.step,
			PixelFormat32bppARGB, pDoc->matImg.data);

		Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 0, 0, 0));	
		memDC.FillRectangle(&blackBrush, 0, 0, memBit.get()->GetWidth(), memBit.get()->GetHeight());	// 도화지 == 검은색

		memDC.DrawImage(&bitmap, 0, 0, bitmap.GetWidth(), bitmap.GetHeight());

		// 실시간 그리기

		for (auto pDraw : pDoc->m_draws) {
			pDraw->Draw(memDC, this);
		}
		if (m_nType && m_bflag) {
			pDoc->m_pDraw->Draw(memDC, this);
		}
	}

	// Annotation

	g.DrawImage(memBit.get(), 0, 0);
}


// CMfcAnnotationView 인쇄

BOOL CMfcAnnotationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMfcAnnotationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMfcAnnotationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMfcAnnotationView 진단

#ifdef _DEBUG
void CMfcAnnotationView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcAnnotationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcAnnotationDoc* CMfcAnnotationView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcAnnotationDoc)));
	return (CMfcAnnotationDoc*)m_pDocument;
}
#endif //_DEBUG


// CMfcAnnotationView 메시지 처리기
// GetCurrentMessage()->wParam 구문은 클릭한 툴바항목의 아이디를 리턴
void CMfcAnnotationView::OnChangeTool(UINT wParam) {
	// 툴바와 메뉴바를 라디오처럼 다루기
	CMfcAnnotationDoc* pDoc = GetDocument();
	m_nType = GetCurrentMessage()->wParam;
	pDoc->m_drawType = m_nType;
	//pDoc->CreateDrawObject();
}

// 현재 선택한 툴바항목과 일치여부에 따라 체크 표시
void CMfcAnnotationView::OnUpdateChangeTool(CCmdUI* pCmdUI) {
	// 범위를 지정해서 각종 컨트롤을 사용할 수 있도록 함
	pCmdUI->SetCheck(m_nType == (int)pCmdUI->m_nID);
}

void CMfcAnnotationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMfcAnnotationDoc* pDoc = GetDocument();
	m_bflag = true;
	SetCapture();

	 pDoc->m_pDraw = pDoc->CreateDrawObject(point);
	 pDoc->m_pDraw->pntLine.clear();
	pDoc->m_pDraw->color = pDoc->m_drawColor;
	pDoc->m_pDraw->thick = pDoc->m_drawThick;
	// String
	if (m_nType == ID_DRAW_STRING)
	{
		CAnnotationDlg dlg;

		Graphics g(memBit.get());
		CTextPtr m_pDraw = static_pointer_cast<CText>(pDoc->m_pDraw);


		m_pDraw->text = dlg.m_strText;
		m_pDraw->fontSize = dlg.m_nSize;
		m_pDraw->pointOld = Gdiplus::Point(point.x, point.y);
		m_pDraw->textAlpha = dlg.m_nOpacity;
		m_pDraw->color = Color(255, 255, 0, 255);


		if (dlg.DoModal() == IDOK)
		{
			m_bflag = false;
			m_pDraw->text = dlg.m_strText;
			m_pDraw->fontSize = dlg.m_nSize;
			m_pDraw->pointOld = Gdiplus::Point(point.x, point.y);
			m_pDraw->textAlpha = dlg.m_nOpacity;
			m_pDraw->color = dlg.SetColor();

			pDoc->m_draws.push_back(m_pDraw);

		}
		else
		{
			m_bflag = false;
			m_pDraw->text = _T(""); // 다이얼로그 취소 눌러도 남아 있어서 빈문자로 만들어 없앰

		}
		
	}
	pDoc->UpdateAllViews(FALSE);

	CView::OnLButtonDown(nFlags, point);
}


void CMfcAnnotationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMfcAnnotationDoc* pDoc = GetDocument();
	ReleaseCapture();

	pDoc->m_pDraw->pointCur.Y = point.y;
	pDoc->m_pDraw->pntLine.push_back(Gdiplus::Point(point.x, point.y));
	pDoc->m_draws.push_back(pDoc->m_pDraw);
	
	m_bflag = false;

	Invalidate(FALSE);


	CView::OnLButtonUp(nFlags, point);
}


void CMfcAnnotationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMfcAnnotationDoc* pDoc = GetDocument();
	
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {
		if (m_nType) {
			pDoc->m_pDraw->pointCur.X = point.x;
			pDoc->m_pDraw->pointCur.Y = point.y;

		}
		pDoc->m_pDraw->pntLine.push_back(Gdiplus::Point(point.x, point.y));
	}
	Invalidate(false);
	CView::OnMouseMove(nFlags, point);
}


void CMfcAnnotationView::OnDrawString()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nType = ID_DRAW_STRING;
}


BOOL CMfcAnnotationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CMfcAnnotationView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	m_bflag = false;
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
