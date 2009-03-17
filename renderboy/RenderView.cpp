//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "RenderView.h"

#include <String.h>

#include <stdio.h>


RenderView::RenderView(BRect frame, const char *name)
	: BView(frame, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW|B_FRAME_EVENTS),
	  fClickPoint(NULL)
{
	SetViewColor(255, 255, 255);
	SetHighColor(0, 0, 0);
	SetFontSize(18);
}


RenderView::~RenderView()
{
}


void
RenderView::Draw(BRect updateRect)
{
	MovePenTo(25, 25);
	DrawString("Hello from RenderBoy!");
	if (fClickPoint) {
		char string[50];
		sprintf(string, " You clicked at (%.0f, %.0f)", fClickPoint->x, fClickPoint->y);
		DrawString(string);
	}
}


void
RenderView::FrameResized(float width, float height)
{
}


void
RenderView::MouseDown(BPoint point)
{
	fClickPoint = new BPoint(point);
	Invalidate();
}

