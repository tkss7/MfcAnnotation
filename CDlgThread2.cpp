// CDlgThread2.cpp: 구현 파일
//

#include "pch.h"
#include "MfcAnnotation.h"
#include "CDlgThread2.h"
#include "CAnnotationDlg.h"

// CDlgThread2

IMPLEMENT_DYNCREATE(CDlgThread2, CWinThread)

CDlgThread2::CDlgThread2()
{
}

CDlgThread2::~CDlgThread2()
{
}

BOOL CDlgThread2::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	m_pDlg = new CAnnotationDlg();
	m_pDlg->ShowWindow(SW_SHOW);
	m_pDlg->UpdateWindow();
	return TRUE;
}

int CDlgThread2::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDlgThread2, CWinThread)
END_MESSAGE_MAP()


// CDlgThread2 메시지 처리기
