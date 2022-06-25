
// MfcAnnotationView.cpp: CMfcAnnotationView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MfcAnnotation.h"
#endif

#include "MfcAnnotationDoc.h"
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
	ON_COMMAND_RANGE(ID_DRAW_RECTANGLE, ID_DRAW_LINE_FREE, OnChangeTool)
	ON_UPDATE_COMMAND_UI_RANGE(ID_DRAW_RECTANGLE, ID_DRAW_LINE_FREE, OnUpdateChangeTool)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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

	//Img load
	Graphics g(pDC->m_hDC);
	if (!(pDoc->matImg.empty())) {
		cvtColor(pDoc->matImg, pDoc->matImg, COLOR_BGR2BGRA);

		Bitmap bitmap((INT)pDoc->matImg.size().width, (INT)pDoc->matImg.size().height, (INT)pDoc->matImg.step,
			PixelFormat32bppARGB, pDoc->matImg.data);

		g.DrawImage(&bitmap, 0, 0, bitmap.GetWidth(), bitmap.GetHeight());
	}

	// Annotation
	for (auto i = 0; i < pDoc->m_draws.size(); i++) {
		pDoc->m_draws[i].Draw(g);
	}

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
	pDoc->m_draw.drawType = m_nType;
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
	SetCapture();
	pDoc->m_draw.pointOld.X = point.x;
	pDoc->m_draw.pointOld.Y = point.y;

	CView::OnLButtonDown(nFlags, point);
}


void CMfcAnnotationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMfcAnnotationDoc* pDoc = GetDocument();
	ReleaseCapture();
	pDoc->m_draw.pointCur.X = point.x;
	pDoc->m_draw.pointCur.Y = point.y;
	
	pDoc->m_draws.push_back(pDoc->m_draw);
	pDoc->m_draw.pntLine.clear();
	Invalidate(FALSE);
	CView::OnLButtonUp(nFlags, point);
}


void CMfcAnnotationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMfcAnnotationDoc* pDoc = GetDocument();
	CClientDC dc(this);
	if (nFlags & MK_LBUTTON) {
		pDoc->m_draw.pntLine.push_back(Gdiplus::Point(point.x, point.y));
	}

	CView::OnMouseMove(nFlags, point);
}
