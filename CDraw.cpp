#include "pch.h"
#include "CDraw.h"

void CDraw::Draw(Graphics& g, CWnd* cwnd)
{

}

Color CDraw::SetColor()
{
	return Color(0, 0, 0, 0);
}


void GRectangle::Draw(Graphics& g, CWnd* cwnd)
{
	g.SetSmoothingMode(SmoothingModeHighQuality);
	//Pen ColorPen(SetColor(), 10.f);
	Pen ColorPen(Color::Red, 10.f);
	g.DrawRectangle(&ColorPen, x, y, width, height);
}

Color GRectangle::SetColor()
{
	return Color(m_RectAlpha, (BYTE)GetRValue(m_RectColor), GetGValue(m_RectColor), GetBValue(m_RectColor));
}

void Circle::Draw(Graphics& g, CWnd* cwnd)
{
	g.SetSmoothingMode(SmoothingModeHighQuality);
	Pen ColorPen(Color::Green, 10.f);
	g.DrawEllipse(&ColorPen, x, y, width, height);
}

Color Circle::SetColor()
{
	return Color(m_CircleAlpha, (BYTE)GetRValue(m_CircleColor), GetGValue(m_CircleColor), GetBValue(m_CircleColor));
}

void DLine::Draw(Graphics& g, CWnd* cwnd)
{
	Pen ColorPen(SetColor(), 10.f);
	g.DrawLine(&ColorPen, Fpoint, Lpoint);
}

Color DLine::SetColor()
{
	return Color(m_DlineAlpa, (BYTE)GetRValue(m_DlineColor), GetGValue(m_DlineColor), GetBValue(m_DlineColor));
}

CLine::CLine()
{
	points.resize(1);
}


void CLine::Draw(Graphics& g, CWnd* cwnd)
{

	g.SetSmoothingMode(SmoothingModeHighQuality);
	Pen ColorPen(SetColor(), 10.f);
	//g.DrawCurve(&ColorPen, points, points.size(), 1.0f);
}

Color CLine::SetColor()
{
	return Color(m_ClineAlpa, (BYTE)GetRValue(m_Clineolor), GetGValue(m_Clineolor), GetBValue(m_Clineolor));
}


