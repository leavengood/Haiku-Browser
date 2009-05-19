//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright 2009, Ryan Leavengood, leavengood@gmail.com
// All rights reserved.
//
// Distributed under the terms of the MIT License.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef RENDER_VIEW_H
#define RENDER_VIEW_H


#include <View.h>


class RenderView : public BView {
	public:
		RenderView(BRect frame, const char *name);
		~RenderView();

		void Draw(BRect updateRect);
		void FrameResized(float width, float height);
		void MouseDown(BPoint point);
		void MouseMoved(BPoint point, uint32 transit, const BMessage* message);
	private:
		BRect fHoverRect;
		bool fInHoverArea;
};

#endif	// RENDER_VIEW_H

