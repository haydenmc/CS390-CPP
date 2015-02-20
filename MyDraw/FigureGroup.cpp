#include "stdafx.h"
#include "FigureGroup.h"


FigureGroup::FigureGroup() : Figure(Figure::FigureType::Group)
{
}

FigureGroup::FigureGroup(FigureGroup & g) : Figure(g) {
	for (int i = 0; i < g.groupFigures.size(); i++) {
		this->groupFigures.push_back(g.groupFigures.at(i)->clone());
	}
}

void FigureGroup::addFigure(Figure * figure) {
	this->groupFigures.insert(this->groupFigures.begin(), figure);
	calculateBounds();
}

void FigureGroup::calculateBounds() {
	auto initialPoint = (*((*(this->groupFigures.begin()))->getControlPoints().begin()));
	int minX = initialPoint->getX();
	int minY = initialPoint->getY();
	int maxX = initialPoint->getX();
	int maxY = initialPoint->getY();
	for (auto iter = this->groupFigures.begin(); iter < this->groupFigures.end(); iter++) {
		for (auto pointIter = (*iter)->getControlPoints().begin(); pointIter < (*iter)->getControlPoints().end(); pointIter++) {
			if ((*pointIter)->getX() < minX) {
				minX = (*pointIter)->getX();
			}
			if ((*pointIter)->getX() > maxX) {
				maxX = (*pointIter)->getX();
			}
			if ((*pointIter)->getY() < minY) {
				minY = (*pointIter)->getY();
			}
			if ((*pointIter)->getY() > maxY) {
				maxY = (*pointIter)->getY();
			}
		}
	}
	while (this->controlPoints.size() > 0) {
		delete this->controlPoints.back();
		this->controlPoints.pop_back();
	}
	controlPoints.push_back(new ControlPoint(this, minX, minY));
	controlPoints.push_back(new ControlPoint(this, maxX, maxY));
	this->width = maxX - minX;
	this->height = maxY - minY;
}

void FigureGroup::draw(CDC* pDC)
{
	for (auto iter = this->groupFigures.begin(); iter < this->groupFigures.end(); iter++) {
		(*iter)->draw(pDC);
	}
}

// Move the control points that are selected an increment dx,dy 
void FigureGroup::dragSelectedControlPoints(int dx, int dy)
{
	// record our current bounds
	int minX = controlPoints.at(0)->getX();
	int minY = controlPoints.at(0)->getY();
	int maxX = controlPoints.at(1)->getX();
	int maxY = controlPoints.at(1)->getY();

	// Move 'em
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		if (c->isSelected()) {
			c->move(c->getX() + dx, c->getY() + dy);
		}
	}

	scaleChildren(minX, minY, maxX, maxY);
}

void FigureGroup::scaleChildren(int minX, int minY, int maxX, int maxY) {
	// record our new bounds
	int newMinX = controlPoints.at(0)->getX();
	int newMinY = controlPoints.at(0)->getY();
	int newMaxX = controlPoints.at(1)->getX();
	int newMaxY = controlPoints.at(1)->getY();

	// Calculate origin shift
	int shiftX = 0, shiftY = 0;
	shiftX = newMinX - minX;
	shiftY = newMinY - minY;

	// Calculate new width / height
	int newWidth = newMaxX - newMinX;
	int newHeight = newMaxY - newMinY;

	// Calculate scale w.r.t. origin
	long double horizontalScale = (double)newWidth / (double)this->width;
	long double verticalScale = (double)newHeight / (double)this->height;

	this->width = newWidth;
	this->height = newHeight;

	// Move child control points
	for (auto iter = this->groupFigures.begin(); iter < this->groupFigures.end(); iter++) {	
		if ((*iter)->figureType == FigureType::Group) {
			int minX = (*iter)->getControlPoints().at(0)->getX();
			int minY = (*iter)->getControlPoints().at(0)->getY();
			int maxX = (*iter)->getControlPoints().at(1)->getX();
			int maxY = (*iter)->getControlPoints().at(1)->getY();
		}
		for (auto pointIter = (*iter)->getControlPoints().begin(); pointIter < (*iter)->getControlPoints().end(); pointIter++) {
			auto point = *pointIter;
			int pointX = point->getX() + shiftX;
			int pointY = point->getY() + shiftY;
			int moveX = 0, moveY = 0;
			moveX = (long double)(pointX - newMinX) * (long double)(horizontalScale - 1);
			moveY = (long double)(pointY - newMinY) * (long double)(verticalScale - 1);
			point->move(pointX + moveX, pointY + moveY);
		}
		if ((*iter)->figureType == FigureType::Group) {
			dynamic_cast<FigureGroup *>(*iter)->scaleChildren(minX, minY, maxX, maxY);
		}
	}
}

vector<Figure *> FigureGroup::getGroupFigures() {
	return groupFigures;
}

// Return true if any of the grouped figures is close to coordinates (x,y)
bool FigureGroup::isCloseTo(int x, int y)
{
	for (auto iter = this->groupFigures.begin(); iter < this->groupFigures.end(); iter++) {
		if ((*iter)->isCloseTo(x, y)) {
			return true;
		}
	}
	return false;
}

void FigureGroup::setFillColor(COLORREF color)
{
	this->fillColor = color;
	for (auto iter = this->groupFigures.begin(); iter < this->groupFigures.end(); iter++) {
		(*iter)->setFillColor(color);
	}
}

FigureGroup * FigureGroup::clone() {
	FigureGroup * clone = new FigureGroup(*this);
	return clone;
}

FigureGroup::~FigureGroup()
{
	for (int i = groupFigures.size() - 1; i >= 0; i--) {
		delete groupFigures.at(i);
	}
}
