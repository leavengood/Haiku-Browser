//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Tab.h"

#include <stdlib.h>
#include <string.h>

Tab::Tab(const char *title)
	: BView("Tab", 0),
	fTitle(NULL)
{
	_InitData(title);
}


Tab::~Tab()
{
	free(fTitle);
}


void
Tab::MessageReceived(BMessage *message)
{
	switch (message->what) {
		default:
			BView::MessageReceived(message);
			break;
	}
}


void
Tab::SetTitle(const char *title)
{
	if (fTitle != NULL) {
		free(fTitle);
		fTitle = NULL;
	}

	if (title != NULL)
		fTitle = strdup(title);
}


const char *
Tab::Title() const
{
	return fTitle;
}


void
Tab::_InitData(const char *title)
{
	SetTitle(title);
}

