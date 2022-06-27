#pragma once
#include "resource.h"

class CDraw;
class CText;
//using CDrawPtr = std::shared_ptr<CDraw>;
//using CTextPtr = std::shared_ptr<CText>;
using CDrawPtr = std::shared_ptr<CDraw>;
using CTextPtr = std::shared_ptr<CText>;

class CDraw
{
public:
	CDraw()
	{

	}

	CDraw(int drawType, Gdiplus::Point point) 
		: drawType(drawType), pointOld(point), pointCur(point) {
		/*thick = 1;*/
	}

	int drawType;	// 타입
	Color color;
	int thick;

	Gdiplus::Point pointOld;
	Gdiplus::Point pointCur;

	vector<Gdiplus::Point>	pntLine;	// 자유선

public:
	virtual void Draw(Gdiplus::Graphics& g, CWnd* cwnd);
};



class CText:public CDraw
{



public:
	CText(int drawType, Gdiplus::Point point)
		: CDraw(drawType, point) {
		//text = _T("");
		//textAlpha = 255;
		//fontSize = 10;
	}
	CText()
	{

	}
	CString text;
	int fontSize;
//	CPoint pointText;
//	COLORREF textColor;
	int textAlpha;
public:
	//CText();
	virtual void Draw(Graphics& g, CWnd* cwnd);
	//Color SetColor();
};

