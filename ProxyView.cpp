//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ProxyView.h"
#include "Constants.h"

#include <Application.h>
#include <String.h>

#include <stdio.h>
#include <syslog.h>


ProxyView::ProxyView(BRect frame, const char *name)
	: BView(frame, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW|B_FRAME_EVENTS)
{
}


ProxyView::~ProxyView()
{
}


void
ProxyView::Draw(BRect updateRect)
{
}


void
ProxyView::FrameResized(float width, float height)
{
}


void
ProxyView::MouseDown(BPoint point)
{
}


