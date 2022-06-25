#pragma once
#include "resource.h"
#include <vector>

class CDraw
{
public:
	int drawType;	// 타입
	Color color;
	int thick = 1;

	Gdiplus::Point pointOld;
	Gdiplus::Point pointCur;

	vector<Gdiplus::Point>	pntLine;	// 자유선

public:
	void Draw(Gdiplus::Graphics& g);
};

