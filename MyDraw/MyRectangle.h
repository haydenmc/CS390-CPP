#pragma once
#include "Figure.h"
class MyRectangle :
	public Figure
{
public:
	MyRectangle(int x0, int y0, int x1, int y1);
	~MyRectangle(void);

	// Draw a rectangle using graphic context pDC
	void draw(CDC* pDC);

	// Return true if rectangle is close to coordinates (x,y)
	bool isCloseTo(int x, int y);

	MyRectangle * clone();
};

