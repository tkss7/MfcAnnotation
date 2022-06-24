#pragma once


// CAnnotationDlg 대화 상자

class CAnnotationDlg : public CDialog
{
	DECLARE_DYNAMIC(CAnnotationDlg)

public:
	CAnnotationDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAnnotationDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAnnotationDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CString m_strText;
	int m_nSize;
	CSliderCtrl m_SliderOp;
	CMFCColorButton m_btnColor;
	COLORREF m_color;
	int m_nOpacity;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditText();
	afx_msg void OnEnChangeEditSize();
	afx_msg void OnBnClickedColorbutton();
	CEdit m_editText;
};
