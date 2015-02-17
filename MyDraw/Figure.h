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

#include <vector>
#include "ControlPoint.h"

using namespace std;

// Defines a generic figure. 
// Other classes like Line, Rectangle, Circle etc. Inherit from Figure.
class Figure
{
public:
	// Figure type. You may need to add more types here
	enum FigureType { Line, Rectangle, Circle, Text, Group };
	// Type of this figure.
	FigureType figureType;
protected:

	COLORREF fillColor;

	// List of all control point for this figure.
	vector<ControlPoint *> controlPoints;

public:

	static const double smallDistance;

	// Constructor and destructor
	Figure(FigureType figureType);
	~Figure(void);

	// Get the list of all control points
	virtual const vector<ControlPoint *> & getControlPoints();

	// Set the fill color
	void setFillColor(COLORREF color);

	// Draw figure. Implemented in subclasses.
	virtual void draw(CDC* pDC) = 0;

	// Draw figure with selected control points
	virtual void drawWithControlPoints(CDC *pDC);

	// Get type of this figure
	virtual FigureType getFigureType() const;

	// Select/deselect all control points
	virtual void select(bool selected);

	// Return true if any of the control points of this figure is selected
	virtual bool isSelected();

	// Select/deselect last control point
	virtual void selectLast(bool selected);

	// Move the control points that are selected an increment dx,dy 
	virtual void dragSelectedControlPoints( int dx, int dy );

	// Select control points that are inside a rectangular area
	virtual void selectControlPointsInArea(int x0, int y0, int x1, int y1);

	// Return true if x,y is close to this figure so it can be selected
	virtual bool isCloseTo(int x, int y) = 0;

	// Find the control point in this figure that encloses x,y
	ControlPoint * findControlPoint(int x, int y);

	// Return true if figure is inside the area described.
	// It defaults to return true if all control points of the figure are
	// inside the rectangle.
	virtual bool isInsideArea(int x0, int y0, int x1, int y1);

	// Distance of point (x0,y0) to the line between (x1,y1) and (x2,y2).
	// If the perpendicular distance is beyond the line segment, it returns a large distance.
	static double distancePointToLine(double x0, double y0, double x1, double y1, double x2, double y2);
};

