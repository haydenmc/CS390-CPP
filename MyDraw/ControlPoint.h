#pragma once

/*
  Copyright (c) 2011
  Gustavo Rodriguez-Rivera
  All rights reserved.

This work was developed by the author(s) at Purdue University
during 2011.

Redistribution and use in source and binary forms are permitted provided that
this entire copyright notice is duplicated in all such copies.  No charge,
other than an "at-cost" distribution fee, may be charged for copies,
derivations, or distributions of this material without the express written
consent of the copyright holders. Neither the name of the University, nor the
name of the author may be used to endorse or promote products derived from
this material without specific prior written permission.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR ANY PARTICULAR PURPOSE.
*/

class Figure;

// A control point is an editable part of a figure
// that can be used to move or resize the figure.
class ControlPoint
{
	// Size of the square that represents a Control Point when selected.
	enum { ControlPointDist = 8 };

	// Figure the control point belongs to
	Figure * figure;

	// Is the control point selected or not.
	bool selected;

	// Coordinates of the control point
	int x;
	int y;
public:
	// Constructor and destructor.
	ControlPoint(Figure * figure, int x, int y);
	~ControlPoint(void);

	// Select/deselect this control point.
	void select(bool selected);

	// Return true if control point is selected.
	bool isSelected();

	// Move this control point to x,y
	void move(int x, int y);

	// Return x, y coordinates of control point.
	int getX() const;
	int getY() const;

	// Draw this control point if it is selected
	void draw(CDC* pDC);

	// Return true if coordinate (x,y) is inside the square that 
	// represents the control point.
	bool isInside(int x, int y);

	// Return true if the control point is inside the rectangle
	// defined by x0, y0, x1, y1
	bool isInsideArea(int x0, int y0, int x1, int y1); 
};

