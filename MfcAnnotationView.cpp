
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
#include "CAnnotationDlg.h"
#include "CText.h"
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
	ON_COMMAND(ID_ANNO_TEXT, &CMfcAnnotationView::OnAnnoText)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMfcAnnotationView 생성/소멸

CMfcAnnotationView::CMfcAnnotationView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_bAnno = false;
	m_bDblCl = false;
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
	CRect rectDraw;
	GetClientRect(rectDraw);
	Bitmap bitmap2(rectDraw.Width(), rectDraw.Height());
	Graphics g(pDC->m_hDC);
	if (!(pDoc->matImg.empty())) {
		cvtColor(pDoc->matImg, pDoc->matImg, COLOR_BGR2BGRA);

		Bitmap bitmap((INT)pDoc->matImg.size().width, (INT)pDoc->matImg.size().height, (INT)pDoc->matImg.step,
			PixelFormat32bppARGB, pDoc->matImg.data);
		Graphics memDC(&bitmap2);
		SolidBrush whiteBrush(Gdiplus::Color(255, 0, 0, 0));
		memDC.FillRectangle(&whiteBrush, 0, 0, rectDraw.Width(), rectDraw.Height());
		//g.DrawImage(&bitmap, 0, 0, bitmap.GetWidth(), bitmap.GetHeight());
		memDC.DrawImage(&bitmap, 0, 0, bitmap.GetWidth(), bitmap.GetHeight());

		if (m_bDblCl)
		{
			//m_text.Draw(g, this);
			m_text.Draw(memDC, this);

		}
		if (pDoc->m_nDrawMode != 0)
		{
			if (pDoc->m_nDrawMode == ID_DRAW_RECTANGLE)
				m_nemo.Draw(memDC, this);
			if (pDoc->m_nDrawMode == ID_DRAW_CIRCLE)
				m_circle.Draw(memDC, this); 
			//m_nemo.Draw(g, this);
		}
		for (auto nemo : pDoc->Rectangles)
		{
			nemo.Draw(memDC, this);
		}
		for (auto circle : pDoc->Circles)
		{
			circle.Draw(memDC, this);
		}
		for (auto AnnoText : pDoc->m_Text)
		{
			//AnnoText.Draw(g, this);
			AnnoText.Draw(memDC, this);
		}

		g.DrawImage(&bitmap2, 0, 0);
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


void CMfcAnnotationView::OnAnnoText()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bAnno = !m_bAnno;

}


void CMfcAnnotationView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMfcAnnotationDoc* pDoc = GetDocument();
	if (m_bAnno)
	{
		m_bDblCl = true;
		CAnnotationDlg dlg;
		CClientDC dc(this);
		Graphics g(dc.m_hDC);
		
		m_text.m_AnnoText = dlg.m_strText;
		m_text.m_AnnoSize= dlg.m_nSize;
		m_text.m_AnnoPoint= point;
		m_text.m_AnnoAlpa = dlg.m_nOpacity;
		m_text.m_AnnoColor= 0xFF00FF;

		m_text.Draw(g, this);


		CText tmp;
		
		if (dlg.DoModal() == IDOK)
		{

			tmp.m_AnnoText = dlg.m_strText;
			tmp.m_AnnoSize = dlg.m_nSize;
			tmp.m_AnnoPoint = point;
			tmp.m_AnnoAlpa = dlg.m_nOpacity;
			tmp.m_AnnoColor = dlg.m_btnColor.GetColor();

			pDoc->m_Text.push_back(tmp);
			m_bDblCl = false;
		}
		else
			m_bDblCl = false;

		pDoc->UpdateAllViews(FALSE);
	}
	


	CView::OnLButtonDblClk(nFlags, point);
}


void CMfcAnnotationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMfcAnnotationDoc* pDoc = GetDocument();

	if (pDoc->m_nDrawMode!=0)
	{
		if (pDoc->m_nDrawMode == ID_DRAW_RECTANGLE)
		{
			m_nemo.x = point.x;
			m_nemo.y = point.y;
		}
		else if (pDoc->m_nDrawMode == ID_DRAW_CIRCLE)
		{
			m_circle.x = point.x;
			m_circle.y = point.y;
		}
	}
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CMfcAnnotationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMfcAnnotationDoc* pDoc = GetDocument();
	CClientDC dc(this);
	Graphics g(dc.m_hDC);
	if (pDoc->m_nDrawMode != 0)
	{
		if (pDoc->m_nDrawMode == ID_DRAW_RECTANGLE)
		{
			m_nemo.width = point.x - m_nemo.x;
			m_nemo.height = point.y - m_nemo.y;
			pDoc->Rectangles.push_back(m_nemo);
		}
		else if (pDoc->m_nDrawMode == ID_DRAW_CIRCLE)
		{
			m_circle.width = point.x - m_circle.x;
			m_circle.height = point.y - m_circle.y;
			pDoc->Circles.push_back(m_circle);
		}
	}
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}


void CMfcAnnotationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMfcAnnotationDoc* pDoc = GetDocument();
	CClientDC dc(this);
	Graphics g(dc.m_hDC);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON && pDoc->m_nDrawMode != 0)
	{
		if (pDoc->m_nDrawMode == ID_DRAW_RECTANGLE)
		{
			m_nemo.width = point.x - m_nemo.x;
			m_nemo.height = point.y - m_nemo.y;
		}
		else if (pDoc->m_nDrawMode == ID_DRAW_CIRCLE)
		{
			m_circle.width = point.x - m_circle.x;
			m_circle.height = point.y - m_circle.y;
		}
		Invalidate(FALSE);
	}

	CView::OnMouseMove(nFlags, point);
}


BOOL CMfcAnnotationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}
