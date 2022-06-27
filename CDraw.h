#pragma once
#include "pch.h"
class CDraw
{


public:
	virtual void Draw(Graphics& g, CWnd* cwnd);
	virtual Color SetColor();
};


class GRectangle : CDraw
{
public:
	int x;
	int y;
	int width;
	int height;
	COLORREF m_RectColor;
	int m_RectAlpha;

public:
	virtual void Draw(Graphics& g, CWnd* cwnd);
	virtual Color SetColor();
};

class Circle : CDraw
{
public:
	int x;
	int y;
	int width;
	int height;
	COLORREF m_CircleColor;
	int m_CircleAlpha;

public:
	virtual void Draw(Graphics& g, CWnd* cwnd);
	virtual Color SetColor();
};

class DLine : CDraw
{
public:
	Gdiplus::Point Fpoint;
	Gdiplus::Point Lpoint;
	COLORREF m_DlineColor;
	int m_DlineAlpa;

public:
	virtual void Draw(Graphics& g, CWnd* cwnd);
	virtual Color SetColor();
};

class CLine : CDraw
{
public:
	vector<Gdiplus::Point> points;
	COLORREF m_Clineolor;
	int m_ClineAlpa;

public:
	CLine();
	virtual void Draw(Graphics& g, CWnd* cwnd);
	virtual Color SetColor();
};



