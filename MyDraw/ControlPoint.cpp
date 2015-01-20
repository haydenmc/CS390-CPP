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
#include "ControlPoint.h"

// Constructor and destructor.
ControlPoint::ControlPoint(Figure * figure, int x, int y)
{
	this->x = x;
	this->y = y;
	this->figure = figure;
	this->selected = false;
}

ControlPoint::~ControlPoint(void)
{
}

// Select/deselect this control point.
void ControlPoint::select(bool selected)
{
	this->selected = selected;
}

// Return true if control point is selected.
bool ControlPoint::isSelected()
{
	return this->selected;
}

// Move this control point to x,y
void ControlPoint::move(int x, int y)
{
	this->x = x;
	this->y = y;
}

// Return x, y coordinates of control point.
int ControlPoint::getX() const
{
	return x;
}

int ControlPoint::getY() const
{
	return y;
}

// Draw this control point if it is selected
void ControlPoint::draw(CDC* pDC)
{
	// Do not draw control pont if not selected
	if (!this->selected) {
		return;
	}

	CPen pen( PS_SOLID, 0, RGB( 255, 0, 0 ) );
	CPen* pOldPen = pDC->SelectObject( &pen );

	int dist = ControlPointDist;
	int dist2 = dist/2;
	pDC->MoveTo(x-dist2, y-dist2);
	pDC->LineTo(x+dist2, y-dist2);
	pDC->LineTo(x+dist2, y+dist2);
	pDC->LineTo(x-dist2, y+dist2);
	pDC->LineTo(x-dist2, y-dist2);
}

// Return true if coordinate (x,y) is inside the square that 
// represents the control point.
bool ControlPoint::isInside(int x, int y)
{
	int dist = ControlPointDist;
	
	if ( x >= getX() - dist/2 && x < getX() + dist/2 && y >= getY() - dist/2 && y < getY() + dist/2) {
		return true;
	}

	return false;
}

// Return true if the control point is inside the rectangle
// defined by x0, y0, x1, y1
bool ControlPoint::isInsideArea(int x0, int y0, int x1, int y1)
{
	// Find minx, miny, maxx, maxy
	int minX = (x0<x1)?x0:x1;
	int minY = (y0<y1)?y0:y1;
	int maxX = (x0>x1)?x0:x1;
	int maxY = (y0>y1)?y0:y1;

	if (getX() >= minX && getX() <= maxX &&
		getY() >= minY && getY() <= maxY) {
		return true;
	}

	return false;
}