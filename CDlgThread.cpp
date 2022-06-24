// CDlgThread.cpp: 구현 파일
//

#include "pch.h"
#include "MfcAnnotation.h"
#include "CDlgThread.h"


// CDlgThread

IMPLEMENT_DYNCREATE(CDlgThread, CWinThread)

CDlgThread::CDlgThread()
{
}

CDlgThread::~CDlgThread()
{
}

BOOL CDlgThread::InitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 초기화를 수행합니다.
	return TRUE;
}

int CDlgThread::ExitInstance()
{
	// TODO:  여기에서 각 스레드에 대한 정리를 수행합니다.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CDlgThread, CWinThread)
END_MESSAGE_MAP()


// CDlgThread 메시지 처리기
