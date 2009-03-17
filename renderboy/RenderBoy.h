//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef RENDER_BOY_H
#define RENDER_BOY_H


#include <Application.h>


class RenderBoy : public BApplication {
	public:
		RenderBoy();
		~RenderBoy();

		void MessageReceived(BMessage *message);
		void ReadyToRun();
		bool QuitRequested();
//  private:
};


#endif	// RENDER_BOY_H

