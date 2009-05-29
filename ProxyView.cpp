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
#include <MessageFilter.h>
#include <String.h>
#include <Window.h>

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
	syslog(LOG_DEBUG, "Tranquility, ProxyView: received mouse down message, forwarding it to be_app");
	_ForwardCurrentMessage();
}


void
ProxyView::MouseMoved(BPoint point, uint32 transit, const BMessage* message)
{
	syslog(LOG_DEBUG, "Tranquility, ProxyView: received mouse moved message, forwarding it to be_app");
	_ForwardCurrentMessage();
}


void
ProxyView::_ForwardCurrentMessage()
{
	BMessage forward(kMsgForward);
	forward.AddMessage("original", Window()->CurrentMessage());
	be_app->PostMessage(&forward);
}

