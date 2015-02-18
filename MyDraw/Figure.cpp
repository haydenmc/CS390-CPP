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

#include "StdAfx.h"

#include "math.h"
#include "Figure.h"
#include "ControlPoint.h"

const double Figure::smallDistance = 10;

// Constructor and destructor
Figure::Figure(FigureType figureType) 
{
	this->figureType = figureType;
	this->fillColor = RGB(0, 0, 0); // default fill color
}

Figure::~Figure(void)
{
}

// Copy constructor
Figure::Figure(Figure &f) {
	this->figureType = f.figureType;
	this->fillColor = f.fillColor;
	for (int i = 0; i < f.controlPoints.size(); i++) {
		ControlPoint * pointCopy = new ControlPoint(*(f.controlPoints.at(i)));
		this->controlPoints.push_back(pointCopy);
	}
}

// Get/Set id of this figure
Figure::FigureType Figure::getFigureType() const
{
	return this->figureType;
}

// Get the list of all control points
const vector<ControlPoint *> & Figure::getControlPoints()
{
	return this->controlPoints;
}

void Figure::setFillColor(COLORREF color)
{
	this->fillColor = color;
}

// Draw figure with control points if selected
void Figure::drawWithControlPoints(CDC *pDC)
{
	// Draw figure
	this->draw(pDC);

	// Draw control points
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		c->draw(pDC);
	}
}

// Select/deselect all control points
void Figure::select(bool selected)
{
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		c->select(selected);
	}
}

// Select/deselect last control point
void Figure::selectLast(bool selected)
{
	if (this->controlPoints.size()>0) {
		ControlPoint * c = controlPoints.at(this->controlPoints.size()-1);
		c->select(selected);
	}
}

// Return true if any of the control points of this figure is selected
bool Figure::isSelected() {
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		if (c->isSelected()) {
			return true;
		}
	}
	return false;
}

// Move the control points that are selected an increment dx,dy 
void Figure::dragSelectedControlPoints( int dx, int dy )
{
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		if (c->isSelected()) {
			c->move(c->getX() + dx, c->getY() + dy);
		}
	}
}

// Select control points that are inside a rectangular area
void Figure::selectControlPointsInArea(int x0, int y0, int x1, int y1)
{
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		if (c->isInsideArea(x0, y0, x1, y1)) {
				c->select(true);
		}
	}
}

// Find the control point in this figure that encloses x,y
ControlPoint * Figure::findControlPoint(int x, int y)
{
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		if (c->isInside(x,y)) {
			return c;
		}
	}
	return NULL;
}

// Return true if figure is inside the area described.
// It defaults to return true if all control points of the figure are
// inside the rectangle.
bool Figure::isInsideArea(int x0, int y0, int x1, int y1) {
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		if (!c->isInsideArea(x0, y0, x1, y1)) {
				return false;
		}
	}
	return true;
}

//
// Distance from point (x0,y0) to the line between (x1,y1) and (x2,y2)
// See http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html
// 
// Using just the distance is not enough. The equation of the distance from the line to a point 
// assumes an infinite line. We also have to check if the perpendicular distance is inside the
// line segment x1,y1 to x2, y2.
//
double Figure::distancePointToLine(double x0, double y0, double x1, double y1, double x2, double y2) {
	double r = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

	const double eps = .00001;
	const double largeDist = 10000;

	// Return a large distance if (x1,y1) and (x2,y2) are almost the same.
	if (r < eps) {
		return largeDist;
	}

	// Make sure that the point is inside the line interval
	double dotProduct = ((x0-x1)*(x2-x1) + (y0-y1)*(y2-y1))/r;
	if (dotProduct < 0 || dotProduct > r) {
		return largeDist;
	}

	// Point is inside line interval.

	// Compute distance line to point.
	double dist = ((x2-x1)*(y1-y0)-(x1-x0)*(y2-y1))/r;

	// Obtain abs value
	dist = (dist>0)?dist:-dist;

	return dist;
}
