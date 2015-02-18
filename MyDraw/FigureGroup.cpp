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
	// Move all of our child figures...
	for (auto iter = this->groupFigures.begin(); iter < this->groupFigures.end(); iter++) {
		if ((*iter)->figureType == FigureType::Group) {
			(*iter)->dragSelectedControlPoints(dx, dy);
		}
		else {
			for (auto pointIter = (*iter)->getControlPoints().begin(); pointIter < (*iter)->getControlPoints().end(); pointIter++) {
				auto point = *pointIter;
				point->move(point->getX() + dx, point->getY() + dy);
			}
		}
	}
	// Move group control points...
	for (unsigned i = 0; i < this->controlPoints.size(); i++) {
		ControlPoint * c = controlPoints.at(i);
		if (c->isSelected()) {
			c->move(c->getX() + dx, c->getY() + dy);
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

FigureGroup * FigureGroup::clone() {
	FigureGroup * clone = new FigureGroup(*this);
	return clone;
}

FigureGroup::~FigureGroup()
{
}
