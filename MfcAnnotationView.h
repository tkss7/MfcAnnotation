
// MfcAnnotationView.h: CMfcAnnotationView 클래스의 인터페이스
//

#pragma once
#include "MfcAnnotationDoc.h"
#include "CText.h"
#include "CDraw.h"
class CMfcAnnotationView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMfcAnnotationView() noexcept;
	DECLARE_DYNCREATE(CMfcAnnotationView)

// 특성입니다.
public:
	CMfcAnnotationDoc* GetDocument() const;

// 작업입니다.
public:
	bool m_bAnno;
	bool m_bDblCl;
	CText m_text;
	GRectangle m_nemo;
	Circle m_circle;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMfcAnnotationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAnnoText();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MfcAnnotationView.cpp의 디버그 버전
inline CMfcAnnotationDoc* CMfcAnnotationView::GetDocument() const
   { return reinterpret_cast<CMfcAnnotationDoc*>(m_pDocument); }
#endif

