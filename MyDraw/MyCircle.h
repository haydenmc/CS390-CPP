#pragma once
#include "Figure.h"
#pragma once
#include "Figure.h"

class MyCircle :
	public Figure
{
public:
	MyCircle(int x0, int y0, int x1, int y1);
	~MyCircle();

	// Draw a circle using graphic context pDC
	void draw(CDC* pDC);

	// Return true if rectangle is close to coordinates (x,y)
	bool isCloseTo(int x, int y);
};

