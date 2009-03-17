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
	private:
		BPoint *fClickPoint;
};

#endif	// RENDER_VIEW_H

