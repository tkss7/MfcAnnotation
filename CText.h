#pragma once
class CText
{
public:
	CString m_AnnoText;
	int m_AnnoSize;
	CPoint m_AnnoPoint;
	COLORREF m_AnnoColor;
	int m_AnnoAlpa;
public:
	CText();
	void Draw(Graphics &g,CWnd* cwnd);

};

