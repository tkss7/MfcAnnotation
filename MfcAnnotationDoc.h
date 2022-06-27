
// MfcAnnotationDoc.h: CMfcAnnotationDoc 클래스의 인터페이스
//


#pragma once
#include "resource.h"
#include "CDraw.h"
#include <vector>

class CMfcAnnotationDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMfcAnnotationDoc() noexcept;
	DECLARE_DYNCREATE(CMfcAnnotationDoc)

// 특성입니다.
public:

// 작업입니다.
public:
	// Img
	CString m_ImgPath;
	Mat matImg;
	Color m_drawColor;
	int m_drawThick;
	//// 정의
	//CDraw m_draw;
	//vector<CDraw*> m_draws;

	//// String
	//CText m_text;
	//vector<CText> m_texts;
	int m_drawType;
	CDrawPtr m_pDraw;
	vector<CDrawPtr> m_draws;

	CDrawPtr CreateDrawObject(CPoint point) {
		switch (m_drawType) {
		case ID_DRAW_STRING:
			m_pDraw = make_shared<CText>(m_drawType, Gdiplus::Point(point.x, point.y));
			break;
		default:
			m_pDraw = make_shared<CDraw>(m_drawType, Gdiplus::Point(point.x, point.y));
			break;
		}
		return m_pDraw;
	}
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMfcAnnotationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnImgLoad();
	afx_msg void OnOptionColor();
	afx_msg void OnThick1();
	afx_msg void OnThick3();
	afx_msg void OnThick5();
};
