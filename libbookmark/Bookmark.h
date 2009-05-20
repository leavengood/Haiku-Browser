// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//  Copyright 2009 Haiku Inc. All rights reserved.
//  Distributed under the terms of the MIT License.
//
//  Author:
// 			Maxime Simon, simon.maxime (at) gmail.com
// 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef BOOKMARK_H
#define BOOKMARK_H


#include <Bitmap.h>
#include <Directory.h>
#include <String.h>

class Bookmark {
	public:
		Bookmark(BString *title, BString *url, BDirectory *parentDirectory = NULL,
		        BBitmap *favicon = NULL);
		~Bookmark();

		BString*	Title();
		BString*	Url();
		BDirectory*	ParentDirectory();
		BBitmap*	Favicon();
		void		SetTitle(BString *title);
		void		SetUrl(BString *url);
		void		SetParentDirectory(BDirectory *parentDirectory);
		void		SetFavicon(BBitmap *favicon);

	private:
		BString		*fTitle;
		BString		*fUrl;
		BDirectory	*fParentDirectory;
		BBitmap		*fFavicon;
};

#endif // BOOKMARK_H
