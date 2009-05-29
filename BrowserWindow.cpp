//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "BrowserWindow.h"
#include "ProxyView.h"

#include <Application.h>
#include <GroupLayout.h>
#include <GroupLayoutBuilder.h>

#include <stdio.h>

BrowserWindow::BrowserWindow()
	: BWindow(BRect(100, 100, 600, 600), "Tranquility", B_DOCUMENT_WINDOW, 0)
{
	fToolbar = new BrowserToolbar();

	fProxyView = new ProxyView(Bounds(), "Proxy");

	// Set the layout
	SetLayout(new BGroupLayout(B_HORIZONTAL));

	AddChild(BGroupLayoutBuilder(B_VERTICAL, 10)
		.Add(fToolbar)
		.Add(fProxyView)
	);
}


BrowserWindow::~BrowserWindow()
{
}


void
BrowserWindow::MessageReceived(BMessage *message)
{
	switch (message->what) {
		default:
			BWindow::MessageReceived(message);
			break;
	}
}


bool
BrowserWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}


void
BrowserWindow::SetViewBitmap(BBitmap *bitmap)
{
	if (Lock()) {
		fProxyView->SetViewBitmap(bitmap);
		Unlock();
	}
}
