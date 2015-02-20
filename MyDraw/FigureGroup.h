#pragma once
#include "Figure.h"
class FigureGroup :
	public Figure
{
private:
	void calculateBounds();
protected:
	vector<Figure *> groupFigures;
public:
	FigureGroup();
	FigureGroup(FigureGroup & g);
	void addFigure(Figure * figure);
	// Draw a group using graphic context pDC
	void draw(CDC* pDC);
	// Return true if rectangle is close to coordinates (x,y)
	bool isCloseTo(int x, int y);
	void dragSelectedControlPoints(int dx, int dy);
	vector<Figure *> getGroupFigures();
	void setFillColor(COLORREF color);
	FigureGroup * clone();
	~FigureGroup();
};

