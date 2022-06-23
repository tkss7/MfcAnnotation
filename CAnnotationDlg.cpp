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
}


BEGIN_MESSAGE_MAP(CAnnotationDlg, CDialog)
//	ON_BN_CLICKED(IDCANCEL, &CAnnotationDlg::OnBnClickedCancel)
//	ON_EN_CHANGE(IDC_TEXT, &CAnnotationDlg::OnEnChangeText)
//	ON_EN_CHANGE(IDC_EDIT_TEXT, &CAnnotationDlg::OnEnChangeEditText)
//ON_EN_CHANGE(IDC_EDIT_TEXT, &CAnnotationDlg::OnEnChangeEditText)
//ON_EN_CHANGE(IDC_EDIT_SIZE, &CAnnotationDlg::OnEnChangeEditSize)
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
