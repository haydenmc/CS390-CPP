#include "stdafx.h"
#include "MyCircle.h"


MyCircle::MyCircle(int x0, int y0, int x1, int y1) : Figure(Figure::FigureType::Circle)
{
	controlPoints.push_back(new ControlPoint(this, x0, y0));
	controlPoints.push_back(new ControlPoint(this, x1, y1));
}


MyCircle::~MyCircle()
{
}


void MyCircle::draw(CDC* pDC)
{
	ControlPoint * p0 = controlPoints.at(0);
	ControlPoint * p1 = controlPoints.at(1);

	// Find minx, miny, maxx, maxy
	int minX = (p0->getX()<p1->getX()) ? p0->getX() : p1->getX();
	int minY = (p0->getY()<p1->getY()) ? p0->getY() : p1->getY();
	int maxX = (p0->getX()<p1->getX()) ? p1->getX() : p0->getX();
	int maxY = (p0->getY()<p1->getY()) ? p1->getY() : p0->getY();

	// Draw circle
	CPen pen(PS_SOLID, 0, RGB(0, 0, 0));
	CBrush fillBrush(this->fillColor);
	pDC->SelectObject(&pen);
	pDC->SelectObject(&fillBrush);
	pDC->Ellipse(minX, minY, maxX, maxY);
}

// Return true if circle is close to coordinates (x,y)
bool MyCircle::isCloseTo(int x, int y)
{
	ControlPoint * p0 = controlPoints.at(0);
	ControlPoint * p1 = controlPoints.at(1);

	// Find minx, miny, maxx, maxy
	int minX = (p0->getX()<p1->getX()) ? p0->getX() : p1->getX();
	int minY = (p0->getY()<p1->getY()) ? p0->getY() : p1->getY();
	int maxX = (p0->getX()<p1->getX()) ? p1->getX() : p0->getX();
	int maxY = (p0->getY()<p1->getY()) ? p1->getY() : p0->getY();

	// Check if (x,y) is close to any of the borders.
	if (Figure::distancePointToLine(x, y, minX, minY, maxX, minY) < Figure::smallDistance ||
		Figure::distancePointToLine(x, y, maxX, minY, maxX, maxY) < Figure::smallDistance ||
		Figure::distancePointToLine(x, y, minX, maxY, maxX, maxY) < Figure::smallDistance ||
		Figure::distancePointToLine(x, y, minX, minY, minX, maxY) < Figure::smallDistance) {
		return true;
	}

	return false;
}
