// CAnnotationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MfcAnnotation.h"
#include "CAnnotationDlg.h"
#include "afxdialogex.h"
#include "MfcAnnotationView.h"
#include "framework.h"
#include "MfcAnnotationDoc.h"
#include "CDraw.h"
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
	CMfcAnnotationDoc* pDoc = (CMfcAnnotationDoc*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	
	UpdateData(TRUE);
	m_nOpacity = m_SliderOp.GetPos();
	UpdateData(FALSE);

	//pDoc->m_pDraw-> = m_nOpacity;
	//dynamic_pointer_cast<CText>(pDoc->m_pDraw).get()->textAlpha = m_nOpacity;
	static_pointer_cast<CText>(pDoc->m_pDraw).get()->textAlpha = m_nOpacity;
	pDoc->m_pDraw->color = SetColor();
	pDoc->UpdateAllViews(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}




void CAnnotationDlg::OnEnChangeEditText()
{
	CMfcAnnotationDoc* pDoc = (CMfcAnnotationDoc*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();

	UpdateData(TRUE);
	m_strText;
	UpdateData(FALSE);
	 
	static_pointer_cast<CText>(pDoc->m_pDraw).get()->text = m_strText;
	//(CText*)(pDoc->m_pDraw).get()->

	pDoc->UpdateAllViews(FALSE);
}


void CAnnotationDlg::OnEnChangeEditSize()
{
	CMfcAnnotationDoc* pDoc = (CMfcAnnotationDoc*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();

	UpdateData(TRUE);
	m_nSize;
	UpdateData(FALSE);

	
	//pDoc->m_pDraw->fontSize = m_nSize;
	static_pointer_cast<CText>(pDoc->m_pDraw).get()->fontSize = m_nSize;

	pDoc->UpdateAllViews(FALSE);
}


void CAnnotationDlg::OnBnClickedColorbutton()
{
	CMfcAnnotationDoc* pDoc = (CMfcAnnotationDoc*)((CFrameWnd*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	UpdateData(TRUE);
	m_color=m_btnColor.GetColor();
	UpdateData(FALSE);

	static_pointer_cast<CText>(pDoc->m_pDraw).get()->color = SetColor();

	pDoc->UpdateAllViews(FALSE);
}

Color CAnnotationDlg::SetColor()
{
	return Color(m_nOpacity, (BYTE)GetRValue(m_color), GetGValue(m_color), GetBValue(m_color));
}

