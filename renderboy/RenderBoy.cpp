//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "RenderBoy.h"
#include "AppSignatures.h"
#include "BrowserWindow.h"
#include "Constants.h"

#include <Alert.h>

#include <stdio.h>
#include <syslog.h>

RenderBoy::RenderBoy()
	: BApplication(kRenderAppSignature),
	fStartMsgReceived(false),
	fMessenger(NULL),
	fRenderFrame(0,0,0,0),
	fRenderBitmap(NULL),
	fRenderView(NULL),
	fDebugWindow(NULL),
	fDebugView(NULL)
{
}


RenderBoy::~RenderBoy()
{
}


void
RenderBoy::ReadyToRun()
{
	if (!fStartMsgReceived) {
		BAlert* alert = new BAlert("Error",
			"Error: RenderBoy is not meant to be run as a stand-alone application.", "Close");
		alert->Go();
		be_app->PostMessage(B_QUIT_REQUESTED);
	} else {
		// Initialize members
		fRenderBitmap = new BBitmap(fRenderFrame, B_RGB32, true);
		fRenderView = new RenderView(fRenderFrame, "Render View");
		fRenderBitmap->AddChild(fRenderView);
		fDebugView = new BView(fRenderFrame, "Debug View", B_FOLLOW_ALL_SIDES, 0);
		BRect debugFrame(fRenderFrame);
		debugFrame.OffsetBy(300, 300);
		fDebugWindow = new BWindow(debugFrame, "RenderBoy Debug Window", B_TITLED_WINDOW, 0);
		fDebugWindow->AddChild(fDebugView);
		fDebugWindow->Show();
		SetPulseRate(1000000L);
	}
}


void
RenderBoy::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case kMsgStartRenderApp:
		{
			BRect renderFrame;
			if (message->FindRect("renderFrame", &renderFrame) == B_OK) {
				char str[100];
				sprintf(str, "RenderBoy: got a renderFrame (%.0f, %.0f, %.0f, %.0f)!",
					renderFrame.left, renderFrame.top, renderFrame.right, renderFrame.bottom);
				syslog(LOG_DEBUG, str);
				fRenderFrame = renderFrame;
				team_id browserTeam;
				if (message->FindInt32("teamID", &browserTeam) == B_OK) {
					sprintf(str, "RenderBoy: got a browser team ID of %d", browserTeam);
					syslog(LOG_DEBUG, str);
					status_t error;
					fMessenger = new BMessenger(kBrowserAppSignature, browserTeam, &error);
					if (error == B_OK)
						// Only set this if everything needed was received correctly
						fStartMsgReceived = true;
					else {
						sprintf(str, 
							"RenderBoy: could not create a valid BMessenger to the browser, error was %d!", error);
						syslog(LOG_DEBUG, str);
					}
				}
			}
			break;
		}

		case kMsgUpdate:
		{
			syslog(LOG_DEBUG, "RenderBoy: received kMsgUpdate message");
			BMessage reply;
			if (_PrepareRenderMessage(&reply));
				message->SendReply(&reply);
			break;
		}

		case kMsgForward:
		{
			syslog(LOG_DEBUG, "RenderBoy: received kMsgForward message");
			BMessage original;
			if (message->FindMessage("original", &original) == B_OK) {
				syslog(LOG_DEBUG, "RenderBoy: found original message from kMsgForward");

				if (fRenderBitmap && fRenderBitmap->Lock()) {
					syslog(LOG_DEBUG, "RenderBoy: sending message to the render view");
					switch (original.what) {
						case B_MOUSE_DOWN:
						{
							BPoint where;
							original.FindPoint("be:view_where", &where);
							fRenderView->MouseDown(where);

							break;
						}
						case B_MOUSE_MOVED:
						{
							// TODO: The BWindow code which processes mouse moved messages does
							// a lot more than this to eliminate redundant messages. It might
							// be better to forward from the ProxyView::MouseMoved instead of
							// using a message filter...
							BPoint where;
							original.FindPoint("be:view_where", &where);
							uint32 transit;
							original.FindInt32("be:transit", (int32*)&transit);
							// Ignore the drag message for now
							fRenderView->MouseMoved(where, transit, NULL);

							break;
						}
					}
					fRenderBitmap->Unlock();
				}
			}
			break;
		}

		default:
			BApplication::MessageReceived(message);
			break;
	}
}


void
RenderBoy::Pulse()
{
	BMessage update;
	if (_PrepareRenderMessage(&update) && fMessenger);
		fMessenger->SendMessage(&update);
}


bool
RenderBoy::QuitRequested()
{
	syslog(LOG_DEBUG, "RenderBoy: received B_QUIT_REQUESTED message, quitting.");
	return true;
}


bool
RenderBoy::_PrepareRenderMessage(BMessage *out)
{
	bool result = false;

	if (fRenderBitmap) {
		out->what = kMsgBitmapData;

		if (fRenderBitmap->Lock()) {
			syslog(LOG_DEBUG, "RenderBoy: drawing the view!");
			// Always draw the full frame for now
			fRenderView->Draw(fRenderFrame);
			// Send all the bitmap data
			fRenderBitmap->Archive(out);

			result = true;

			fRenderBitmap->Unlock();
		}

		// Display what was drawn for debugging
		if (fDebugWindow->Lock()) {
			fDebugView->SetViewBitmap(fRenderBitmap);
			fDebugWindow->Unlock();
		}
	} else
		syslog(LOG_DEBUG, "RenderBoy: the fRenderBitmap is NULL, cannot draw!");

	return result;
}


//	#pragma mark -


int
main(int, char **)
{
	RenderBoy renderer;
	renderer.Run();
	return 0;
}

