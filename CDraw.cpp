#include "pch.h"
#include "CDraw.h"

void CDraw::Draw(Gdiplus::Graphics& g)
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
		g.DrawCurve(&pen, pntLine.data(), pntLine.size());
	}
}

CText::CText()
{
	pointText = (0, 0);
	text = (_T(""));
	fontSize = 0;
	textColor = (0xFF00FF);
}

void CText::Draw(Graphics& g, CWnd* cwnd)
{
	CRect rect;
	cwnd->GetClientRect(rect);
	Gdiplus::Font font(_T("Arial"), fontSize, FontStyleBold, UnitPixel);
	SolidBrush sbrush(SetColor());
	Pen pen(Color::Red);


	RectF layoutRect(0.0f, 0.0f, rect.Width(), rect.Height());

	RectF boundRect;
	StringFormat format;
	format.SetAlignment(StringAlignmentNear);
	format.SetLineAlignment(StringAlignmentCenter);
	g.MeasureString(text, -1, &font, layoutRect, &format, &boundRect);

	g.DrawRectangle(&Pen(Color::Red), RectF(pointText.x, pointText.y, boundRect.Width, boundRect.Height));

	g.DrawString(text, -1, &font,
		RectF(pointText.x, pointText.y, boundRect.Width, boundRect.Height),
		&format,
		&sbrush);

}

Color CText::SetColor()
{
	return Color(textAlpha, (BYTE)GetRValue(textColor), GetGValue(textColor), GetBValue(textColor));
}

