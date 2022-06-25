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
		g.DrawLines(&pen, pntLine.data(), pntLine.size());
	}
}