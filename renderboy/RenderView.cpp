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
#include <syslog.h>


RenderView::RenderView(BRect frame, const char *name)
	: BView(frame, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW|B_FRAME_EVENTS),
	  fClickPoint(NULL)
{
	SetViewColor(255, 255, 255);
	SetLowColor(255, 255, 255);
	SetHighColor(240, 67, 67);
}


RenderView::~RenderView()
{
}


void
RenderView::Draw(BRect updateRect)
{
	static int count = 0;

	BRect frame = Frame();
	// Erase previous drawing (this is the lazy and slow way)
	FillRect(frame, B_SOLID_LOW);

	frame.InsetBy(50, 50);
	StrokeEllipse(frame);
	
	MovePenTo(25, 25);
	rgb_color color = HighColor();
	char str[100];
	sprintf(str, "Hello from RenderBoy! Count is %d, high color is RGB(%d, %d, %d)",
		count, color.red, color.green, color.blue);
	DrawString(str);

	// Change the color for next Draw call
	color.red += 3;
	color.green += 3;
	color.blue += 3;
	SetHighColor(color);

	count++;
}


void
RenderView::FrameResized(float width, float height)
{
}


void
RenderView::MouseDown(BPoint point)
{
	char str[100];
	sprintf(str, "RenderBoy, RenderView: received MouseDown message at (%.0f, %.0f)", point.x, point.y);
	syslog(LOG_DEBUG, str);
}

