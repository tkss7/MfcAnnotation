#include "pch.h"
#include "CText.h"

CText::CText()
{
	m_AnnoPoint = (0, 0);
	m_AnnoText=(_T(""));
	m_AnnoSize = 0;
}

void CText::Draw(Graphics& g, CWnd* cwnd)
{
	CRect rect;
	cwnd->GetClientRect(rect);
	Gdiplus::Font font(_T("Arial"), m_AnnoSize, FontStyleBold, UnitPixel);
	SolidBrush sbrush(Color::Black);
	Pen pen(Color::Red);


	RectF layoutRect(0.0f,0.0f,rect.Width(),rect.Height());

	RectF boundRect;
	StringFormat format;
	format.SetAlignment(StringAlignmentNear);
	format.SetLineAlignment(StringAlignmentCenter);
	g.MeasureString(m_AnnoText, -1, &font, layoutRect, &format, &boundRect);
	// Draw a rectangle that represents the size of the string.
	g.DrawRectangle(&Pen(Color::Red), RectF(m_AnnoPoint.x,m_AnnoPoint.y,boundRect.Width,boundRect.Height));
	
	g.DrawString(m_AnnoText, -1, &font,
		RectF(m_AnnoPoint.x, m_AnnoPoint.y, boundRect.Width, boundRect.Height),
		&format,
		&sbrush);

}