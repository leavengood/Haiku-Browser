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

#include <stdio.h>
#include <syslog.h>


class ProxyFilter : public BMessageFilter {
	public:
		ProxyFilter()
			: BMessageFilter(B_ANY_DELIVERY, B_ANY_SOURCE) {}

		virtual filter_result Filter(BMessage* message, BHandler** target);
};


filter_result
ProxyFilter::Filter(BMessage* message, BHandler** target)
{
	// TODO: Check that target is the view
	switch (message->what) {
		// Forward all standard messages to the render process
		case B_MOUSE_DOWN:
		//case B_MOUSE_UP:
		case B_MOUSE_MOVED:
		//case B_KEY_DOWN:
		//case B_KEY_UP:
		{
			syslog(LOG_DEBUG, "Tranquility, ProxyFilter: received mouse down message, forwarding it to be_app");
			BMessage forward(kMsgForward);
			forward.AddMessage("original", message);
			be_app->PostMessage(&forward);
		}
	}

	return B_DISPATCH_MESSAGE;
}


ProxyView::ProxyView(BRect frame, const char *name)
	: BView(frame, name, B_FOLLOW_ALL_SIDES, B_WILL_DRAW|B_FRAME_EVENTS)
{
	AddFilter(new ProxyFilter());
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


