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

using namespace std;

#include "Figure.h"
#include "Line.h"

// This is the main class for the drawing editor.
// It also represents the whole drawing. 
// A Drawing is a group of figures. 
class Drawing
{
public:
	// Mode of the Drawing editor.
	enum EditMode {SelectMode, NewLineMode, NewRectangleMode, NewCircleMode };

	// Mouse Button Mode.
	enum MouseMode { NoButtonPressed, ButtonPressed };

private:

	// This is the list of all the figures in the drawing.
	vector<Figure *> figures;

	// Place to store the figures copied.
	vector<Figure *> clipboard;

	// Current Edit mode. When the new line is selected in the Figure menu, the NewLineMode is set here.
	EditMode editMode;

	// Previous mouse mode.
	MouseMode previousMouseMode;

	// Color used to fill figures
	COLORREF colorFill;

	//Figure * selectedFigure;

	// Previous x and y of the mouse
	int previousX;
	int previousY;

	// Enables or disables the selection rectangle. 
	// If disabled, the draw method will not draw the selection rectangle.
	bool selectionRectangleEnabled;

	// Coordinates of the selection rectangle.
	int selectionRectangleX0, selectionRectangleY0, selectionRectangleX1, selectionRectangleY1;

public:
	// Constructor/Destructor
	Drawing(void);
	~Drawing(void);

	// Draw the figures in the Drawing.
	// Called by the draw method in MyDrawView
	void draw(CDC* pDC);

	// Set the edit mode for the editor.
	void setEditMode(EditMode mode);

	// Set the fill color to be applied to new figures.
	void setFillColor(COLORREF color);

	// Delete any selected figure.
	void deleteSelected(CView * cview);

	// Join selected figures into a new group figure.
	void groupSelected(CView * cview);

	// Split selected group into individual figures.
	void ungroupSelected(CView * cview);

	// Send selected to front
	void sendSelectedToFront(CView * cview);

	// Send selected to back
	void sendSelectedToBack(CView * cview);

	void copySelected(CView * cview);

	void paste(CView * cview);

	// Call back when the mouse is pressed, moved, or released.
	// It is called by the mouse call backs in MyDrawView
	void OnMouse(CView * cview, int nFlags, CPoint point);

	// Select all the control points of the all the figures in the drawing.
	void selectAll(bool selected);

	// Return true if any of the control points in the figures is selected
	bool isSelected();

	// Enable and update coordinates of selection rectangle
	void updateSelectionRectangle(int x0, int y0, int x1, int y1);

	// Disable selection rectangle
	void disableSelectionRectangle();

	// Draw selection rectangle if enabled
	void drawSelectionRectangle(CDC *pDC);

	// Move an increment dx, dy the selected control points.
	void dragSelectedControlPoints( int dx, int dy );

	// Find the control point that encloses the coordinates (x,y)
	ControlPoint * findControlPoint(int x, int y);

	// Select figures that are inside a rectangular area
	void selectFiguresInArea(int x0, int y0, int x1, int y1);

	// Return the figure selected or unselected that is close to the coordinate (x,y)
	Figure * isAnyFigureCloseTo(int x, int y);

	// Return true if there is a selected figure close to (x,y)
	bool isAnySelectedFigureCloseTo(int x, int y);
};

