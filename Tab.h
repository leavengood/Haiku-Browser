//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef TAB_H
#define TAB_H

#include <Message.h>
#include <View.h>


class Tab : public BView {
	public:
		Tab(const char *title);
		~Tab();

		void MessageReceived(BMessage *message);
		void SetTitle(const char *title);
		const char * Title() const;
	private:
		void _InitData(const char *title);
		char *fTitle;
};

#endif	// TAB_H

