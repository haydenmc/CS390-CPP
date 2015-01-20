#pragma once

#include "Figure.h"

// Subclass for a Line. 
// Inherits most methods from Figure. 
class Line : public Figure
{
public:
	// Constructor/destructor for a line
	Line(int x0, int y0, int x1, int y1);
	~Line(void);

	// Draw a line using graphic context pDC
	void draw(CDC* pDC);

	// Return true if line can be selected by clicking on coordinates (x,y)
	//bool selectFigureAt(int x, int y);

	// Return true if line is close to coordinates (x,y)
	bool isCloseTo(int x, int y);
};

