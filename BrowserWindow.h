//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef BROWSER_WINDOW_H
#define BROWSER_WINDOW_H

#include <Window.h>

#include "BrowserToolbar.h"
#include "ProxyView.h"

class BrowserWindow : public BWindow {
	public:
		BrowserWindow();
		~BrowserWindow();

		void MessageReceived(BMessage *message);
		bool QuitRequested();

		void SetViewBitmap(BBitmap *bitmap);

	private:
		void _BuildToolbar();

		BrowserToolbar *fToolbar;
		ProxyView *fProxyView;
};

#endif	// BROWSER_WINDOW_H

