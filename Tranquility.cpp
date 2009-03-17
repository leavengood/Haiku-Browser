//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Tranquility.h"
#include "BrowserWindow.h"

#include <Alert.h>
//#include <MessageRunner.h>
#include <OS.h>
//#include <Path.h>
//#include <String.h>


extern const char *kApplicationSignature = "application/x-vnd.RJL-Tranquility";


Tranquility::Tranquility()
	: BApplication(kApplicationSignature)
{
}


Tranquility::~Tranquility()
{
}


void
Tranquility::AboutRequested()
{
	BAlert* alert = new BAlert("About Tranquility",
		"Tranquility Web Browser\n\nby Ryan Leavengood", "Sweet!");
	alert->Go();
}


void
Tranquility::ReadyToRun()
{
	BrowserWindow *win = new BrowserWindow();
	win->Show();
}


void
Tranquility::MessageReceived(BMessage *message)
{
	switch (message->what) {
		default:
			BApplication::MessageReceived(message);
			break;
	}
}


bool
Tranquility::QuitRequested()
{
	return true;
}


//	#pragma mark -


int
main(int, char **)
{
	Tranquility browser;
	browser.Run();
	return 0;
}

