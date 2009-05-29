//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Maxime Simon, simon.maxime@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef BROWSER_TOOLBAR_H
#define BROWSER_TOOLBAR_H

#include <Bitmap.h>
#include <Toolbar.h>

class BrowserToolbar : public WToolbar {
	public:
		BrowserToolbar();
		virtual ~BrowserToolbar();

	private:
		BBitmap* _RetrieveBitmap(const char *name);
};

#endif // BROWSER_TOOLBAR_H
