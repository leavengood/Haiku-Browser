//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Tranquility.h"
#include "AppSignatures.h"
#include "BrowserWindow.h"
#include "Constants.h"

#include <Alert.h>
#include <Bitmap.h>
#include <OS.h>
#include <Roster.h>
#include <String.h>

#include <syslog.h>

Tranquility::Tranquility()
	: BApplication(kBrowserAppSignature),
	fMessenger(NULL)
{
}


Tranquility::~Tranquility()
{
	delete fMessenger;
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
	fBrowserWindow = new BrowserWindow();

	be_roster->StartWatching(be_app_messenger, B_REQUEST_QUIT);

	BMessage startMsg(kMsgStartRenderApp);
	startMsg.AddRect("renderFrame", fBrowserWindow->Bounds());
	startMsg.AddInt32("teamID", be_app->Team());

	team_id renderTeam;
	if (be_roster->Launch(kRenderAppSignature, &startMsg, &renderTeam) != B_OK) {
		BAlert* alert = new BAlert("Error!",
			"There was an error trying to launch the render process!", "Damn!");
		alert->Go();
	} else {
		fMessenger = new BMessenger(kRenderAppSignature, renderTeam);
	}

	fBrowserWindow->Show();
}


void
Tranquility::MessageReceived(BMessage *message)
{
	switch (message->what) {
		case kMsgUpdate:
		{
			if (fMessenger)
				fMessenger->SendMessage(message);
			break;
		}

		case kMsgBitmapData:
		{
			syslog(LOG_DEBUG, "Tranquility: received kMsgBitmapData message");
			BBitmap *bitmap = dynamic_cast<BBitmap*>(BBitmap::Instantiate(message));
			if (bitmap != NULL) {
				fBrowserWindow->SetViewBitmap(bitmap);
				delete bitmap;
			} else {
				syslog(LOG_DEBUG, "Tranquility: bitmap from message is not valid!");
			}
			// Code to create the bitmap from raw data and a bytes per row (bpr) value
			/*int32 length = 0;
			const void *data;
			if (message->FindData("data", B_RAW_TYPE, &data, &length) == B_OK) {
				int32 bpr;
				if (message->FindInt32("bpr", &bpr) == B_OK) {
					syslog(LOG_DEBUG, "Tranquility: got bpr from kMsgBitmapData message");
					BBitmap bitmap(fBrowserWindow->Bounds(), B_RGB32);
					bitmap.ImportBits(data, length, bpr, 0, B_RGB32);
					fBrowserWindow->SetViewBitmap(&bitmap);
				}
			}*/
			break;
		}

		case B_SOME_APP_QUIT:
		{
			BString sig;
			if (message->FindString("be:signature", &sig) == B_OK) {
				if (sig.Compare(kRenderAppSignature) == 0) {
					BAlert* alert = new BAlert("Error!",
						"The render process has quit!", "Damn!");
					alert->Go();
					fMessenger = NULL;
				}
			}
			break;
		}
		default:
			BApplication::MessageReceived(message);
			break;
	}
}


bool
Tranquility::QuitRequested()
{
	be_roster->StopWatching(be_app_messenger);
	if (fMessenger)
		fMessenger->SendMessage(B_QUIT_REQUESTED);
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

