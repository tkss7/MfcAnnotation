// CAnnotationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MfcAnnotation.h"
#include "CAnnotationDlg.h"
#include "afxdialogex.h"
#include "MfcAnnotationView.h"
#include "framework.h"
#include "MfcAnnotationDoc.h"
// CAnnotationDlg 대화 상자

IMPLEMENT_DYNAMIC(CAnnotationDlg, CDialog)

CAnnotationDlg::CAnnotationDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAnnotationDlg, pParent)
	, m_strText(_T("Click to edit text"))
	, m_nSize(10)
	, m_nOpacity(255)
	, m_color(0xFF00FF)
{

}

CAnnotationDlg::~CAnnotationDlg()
{
}

void CAnnotationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_nSize);
	DDX_Control(pDX, IDC_SLIDER_OPACITY, m_SliderOp);
	DDX_Control(pDX, IDC_COLORBUTTON, m_btnColor);
	DDX_Text(pDX, IDC_COLORBUTTON, m_color);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_editText);
}


BEGIN_MESSAGE_MAP(CAnnotationDlg, CDialog)

ON_WM_HSCROLL()
ON_EN_CHANGE(IDC_EDIT_TEXT, &CAnnotationDlg::OnEnChangeEditText)
ON_EN_CHANGE(IDC_EDIT_SIZE, &CAnnotationDlg::OnEnChangeEditSize)
ON_BN_CLICKED(IDC_COLORBUTTON, &CAnnotationDlg::OnBnClickedColorbutton)
END_MESSAGE_MAP()


// CAnnotationDlg 메시지 처리기




BOOL CAnnotationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_strText = _T("Click to edit text");
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_SliderOp.SetRange(0, 255);
	m_SliderOp.SetPos(255);
	m_SliderOp.SetTicFreq(1);
	
	m_btnColor.SetColor(0xFF00FF);
	m_color = (0xFF00FF);
	m_editText.SetWindowTextW(m_strText);
	m_editText.SetSel(0, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CAnnotationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);
	m_nOpacity = m_SliderOp.GetPos();
	UpdateData(FALSE);

	//CMfcAnnotationDoc* pDoc = (CMfcAnnotationDoc*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	CMfcAnnotationView* pView = (CMfcAnnotationView*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
	pView->m_text.m_AnnoAlpa = m_nOpacity;
	//pDoc->UpdateAllViews(FALSE);
	pView->Invalidate(FALSE);
	//Invalidate();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}




void CAnnotationDlg::OnEnChangeEditText()
{

	UpdateData(TRUE);
	m_strText;
	UpdateData(FALSE);

	//CMfcAnnotationDoc* pDoc = (CMfcAnnotationDoc*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	CMfcAnnotationView* pView = (CMfcAnnotationView*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
	pView->m_text.m_AnnoText = m_strText;

	pView->Invalidate(FALSE);

	
}


void CAnnotationDlg::OnEnChangeEditSize()
{

	UpdateData(TRUE);
	m_nSize;
	UpdateData(FALSE);

	//CMfcAnnotationDoc* pDoc = (CMfcAnnotationDoc*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	CMfcAnnotationView* pView = (CMfcAnnotationView*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
	pView->m_text.m_AnnoSize = m_nSize;

	pView->Invalidate(FALSE);

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAnnotationDlg::OnBnClickedColorbutton()
{
	UpdateData(TRUE);
	m_color=m_btnColor.GetColor();
	UpdateData(FALSE);

	//CMfcAnnotationDoc* pDoc = (CMfcAnnotationDoc*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	CMfcAnnotationView* pView = (CMfcAnnotationView*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveView();
	pView->m_text.m_AnnoColor = m_color;

	pView->Invalidate(FALSE);
}


