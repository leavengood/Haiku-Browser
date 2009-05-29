//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "BrowserToolbar.h"

#include <ToolbarButton.h>
#include <ToolbarSeparator.h>

#include "Constants.h"

BrowserToolbar::BrowserToolbar()
	: WToolbar(BRect(0, 0, 1, 1), "main toolbar")
{
	AddItem(new WToolbarButton("Back", "Back", NULL, new BMessage(kMsgNavBack)),
		0, W_TOOLBAR_LAST_POSITION);

	AddItem(new WToolbarButton("Forward", "Forward", NULL, new BMessage(kMsgNavForward)),
		0, W_TOOLBAR_LAST_POSITION);

	AddItem(new WToolbarButton("Reload", "Reload", NULL, new BMessage(kMsgNavReload)),
		0, W_TOOLBAR_LAST_POSITION);

	AddItem(new WToolbarButton("Home", "Home", NULL, new BMessage(kMsgNavHome)),
		0, W_TOOLBAR_LAST_POSITION);

	AddItem(new WToolbarSeparator(), 0, W_TOOLBAR_LAST_POSITION);

	AddItem(new WToolbarButton("Stop", "Stop", NULL, new BMessage(kMsgNavStop)),
		0, W_TOOLBAR_LAST_POSITION);

	SetLabelPosition(W_TOOLBAR_LABEL_BOTTOM);
}

BrowserToolbar::~BrowserToolbar()
{
	
}
