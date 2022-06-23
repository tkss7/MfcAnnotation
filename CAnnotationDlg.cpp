// CAnnotationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MfcAnnotation.h"
#include "CAnnotationDlg.h"
#include "afxdialogex.h"


// CAnnotationDlg 대화 상자

IMPLEMENT_DYNAMIC(CAnnotationDlg, CDialog)

CAnnotationDlg::CAnnotationDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAnnotationDlg, pParent)
	, m_strText(_T(""))
	, m_nSize(0)
	, m_nOpacity(255)
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
}


BEGIN_MESSAGE_MAP(CAnnotationDlg, CDialog)
//	ON_BN_CLICKED(IDCANCEL, &CAnnotationDlg::OnBnClickedCancel)
//	ON_EN_CHANGE(IDC_TEXT, &CAnnotationDlg::OnEnChangeText)
//	ON_EN_CHANGE(IDC_EDIT_TEXT, &CAnnotationDlg::OnEnChangeEditText)
//ON_EN_CHANGE(IDC_EDIT_TEXT, &CAnnotationDlg::OnEnChangeEditText)
//ON_EN_CHANGE(IDC_EDIT_SIZE, &CAnnotationDlg::OnEnChangeEditSize)
ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_COLORBUTTON, &CAnnotationDlg::OnBnHotItemChangeColorbutton)
//ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_OPACITY, &CAnnotationDlg::OnNMCustomdrawSliderOpacity)
ON_WM_HSCROLL()
//ON_BN_CLICKED(IDC_COLORBUTTON, &CAnnotationDlg::OnBnClickedColorbutton)
END_MESSAGE_MAP()


// CAnnotationDlg 메시지 처리기


//void CAnnotationDlg::OnBnClickedCancel()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialog::OnCancel();
//}


//void CAnnotationDlg::OnEnChangeText()
//{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


//void CAnnotationDlg::OnEnChangeEditText()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CDialog::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


//void CAnnotationDlg::OnEnChangeEditText()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CDialog::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


//void CAnnotationDlg::OnEnChangeEditSize()
//{
//	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
//	// CDialog::OnInitDialog() 함수를 재지정 
//	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
//	// 이 알림 메시지를 보내지 않습니다.
//
//	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


void CAnnotationDlg::OnBnHotItemChangeColorbutton(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 이 기능을 사용하려면 Internet Explorer 6 이상이 필요합니다.
	// _WIN32_IE 기호는 0x0600보다 크거나 같아야 합니다.
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_btnColor.SetColor(m_color);
	*pResult = 0;
}


BOOL CAnnotationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_SliderOp.SetRange(0, 255);
	m_SliderOp.SetPos(255);
	m_SliderOp.SetTicFreq(1);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


//void CAnnotationDlg::OnNMCustomdrawSliderOpacity(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//}


void CAnnotationDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_nOpacity = m_SliderOp.GetPos();


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


//void CAnnotationDlg::OnBnClickedColorbutton()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}
