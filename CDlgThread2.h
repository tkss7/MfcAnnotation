#pragma once



// CDlgThread2

class CDlgThread2 : public CWinThread
{
	DECLARE_DYNCREATE(CDlgThread2)

public:
	CDlgThread2();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CDlgThread2();
	CDialog* m_pDlg;
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


