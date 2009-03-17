//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ProxyView.h"

#include <String.h>

#include <stdio.h>


ProxyView::ProxyView(BRect frame, const char *name)
	: BView(frame, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW|B_FRAME_EVENTS),
	  fClickPoint(NULL)
{
	SetViewColor(255, 255, 255);
	SetHighColor(0, 0, 0);
	SetFontSize(18);
}


ProxyView::~ProxyView()
{
}


void
ProxyView::Draw(BRect updateRect)
{
	MovePenTo(25, 25);
	DrawString("Hello from Tranquility!");
	if (fClickPoint) {
		char string[50];
		sprintf(string, " You clicked at (%.0f, %.0f)", fClickPoint->x, fClickPoint->y);
		DrawString(string);
	}
}


void
ProxyView::FrameResized(float width, float height)
{
}


void
ProxyView::MouseDown(BPoint point)
{
	fClickPoint = new BPoint(point);
	Invalidate();
}

