#pragma once



// CDlgThread

class CDlgThread : public CWinThread
{
	DECLARE_DYNCREATE(CDlgThread)

protected:
	CDlgThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CDlgThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


