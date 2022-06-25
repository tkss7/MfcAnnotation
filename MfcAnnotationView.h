
// MfcAnnotationView.h: CMfcAnnotationView 클래스의 인터페이스
//

#pragma once


class CMfcAnnotationView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMfcAnnotationView() noexcept;
	DECLARE_DYNCREATE(CMfcAnnotationView)

// 특성입니다.
public:
	CMfcAnnotationDoc* GetDocument() const;
	int m_nType;
// 작업입니다.
public:

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
	afx_msg void OnChangeTool(UINT wParam);				// 툴바와 메뉴바를 라디오처럼 다루기
	afx_msg void OnUpdateChangeTool(CCmdUI* pCmdUI);	// 범위를 지정해서 각종 컨트롤을 사용할 수 있도록 함
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MfcAnnotationView.cpp의 디버그 버전
inline CMfcAnnotationDoc* CMfcAnnotationView::GetDocument() const
   { return reinterpret_cast<CMfcAnnotationDoc*>(m_pDocument); }
#endif

