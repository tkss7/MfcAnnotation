#include "pch.h"
#include "CDraw.h"

void CDraw::Draw(Gdiplus::Graphics& g, CWnd* cwnd)
{
	Pen pen(color, thick);
	int width = pointCur.X - pointOld.X;
	int height = pointCur.Y - pointOld.Y;

	if (drawType == ID_DRAW_RECTANGLE) {			//사각형
		g.DrawRectangle(&pen, pointOld.X, pointOld.Y,
			width,
			height);
	}
	else if (drawType == ID_DRAW_ELLIPSE) {		// 원
		g.DrawEllipse(&pen, pointOld.X, pointOld.Y,
			width,
			height);
	}
	else if (drawType == ID_DRAW_LINE_STRAIGHT) {
		g.DrawLine(&pen, pointOld, pointCur);
	}
	else if (drawType == ID_DRAW_LINE_FREE) {
		g.DrawCurve(&pen, pntLine.data(), pntLine.size(),0.5f);
		//g.DrawLines(&pen, pntLine.data(), pntLine.size());
	}
}

//CText::CText() :CDraw()
//{
//	//pointText = (0, 0);
//	text = (_T(""));
//	fontSize = 0;
//	//textColor = (0xFF00FF);
//}

void CText::Draw(Graphics& g, CWnd* cwnd)
{
	if (drawType == ID_DRAW_STRING)
	{
		CRect rect;
		cwnd->GetClientRect(rect);
		Gdiplus::Font font(_T("Arial"), fontSize, FontStyleBold, UnitPixel);
		SolidBrush sbrush(color);
		Pen pen(Color::Red);


		RectF layoutRect(0.0f, 0.0f, rect.Width(), rect.Height());

		RectF boundRect;
		StringFormat format;
		format.SetAlignment(StringAlignmentNear);
		format.SetLineAlignment(StringAlignmentCenter);
		g.MeasureString(text, -1, &font, layoutRect, &format, &boundRect);
		g.DrawRectangle(&Pen(Color::Red), RectF((float)pointOld.X, pointOld.Y, boundRect.Width, boundRect.Height));

		g.DrawString(text, -1, &font,
			RectF(pointOld.X, pointOld.Y, boundRect.Width, boundRect.Height),
			&format,
			&sbrush);
	}
	

}

//Color CText::SetColor()
//{
//	return Color(textAlpha, (BYTE)GetRValue(textColor), GetGValue(textColor), GetBValue(textColor));
//}

