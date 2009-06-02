//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef TAB_BAR_H
#define TAB_BAR_H

#include <Message.h>
#include <View.h>


class TabBar : public BView {
	public:
		TabBar();
		~TabBar();

		void FrameResized(float width, float height);
		void MessageReceived(BMessage *message);
};

#endif	// TAB_BAR_H

