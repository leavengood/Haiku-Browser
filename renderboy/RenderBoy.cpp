//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "RenderBoy.h"
#include "BrowserWindow.h"
#include "Constants.h"

#include <Alert.h>


RenderBoy::RenderBoy()
	: BApplication(kRenderAppSignature)
{
}


RenderBoy::~RenderBoy()
{
}


void
RenderBoy::ReadyToRun()
{
	BAlert* alert = new BAlert("Hello!",
		"This is RenderBoy!", "That's Nice");
	alert->Go();
	PostMessage(B_QUIT_REQUESTED);
}


void
RenderBoy::MessageReceived(BMessage *message)
{
	switch (message->what) {
		default:
			BApplication::MessageReceived(message);
			break;
	}
}


bool
RenderBoy::QuitRequested()
{
	return true;
}


//	#pragma mark -


int
main(int, char **)
{
	RenderBoy renderer;
	renderer.Run();
	return 0;
}

