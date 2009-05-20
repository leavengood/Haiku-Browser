// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//  Copyright 2009 Haiku Inc. All rights reserved.
//  Distributed under the terms of the MIT License.
//
//  Author:
// 			Maxime Simon, simon.maxime (at) gmail.com
// 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "Bookmark.h"

Bookmark::Bookmark(BString *title, BString *url, BDirectory *parentDirectory,
	BBitmap *favicon)
	: fTitle(title),
	fUrl(url),
	fParentDirectory(parentDirectory),
	fFavicon(favicon)
{
}


Bookmark::~Bookmark()
{
}


BString*
Bookmark::Title()
{
	BString *title = new BString(*fTitle);
	return title;
}


BString*
Bookmark::Url()
{
	BString *url = new BString(*fUrl);
	return url;
}


BDirectory*
Bookmark::ParentDirectory()
{
	if (fParentDirectory == NULL)
		return NULL;
	else
		return new BDirectory(*fParentDirectory);
}


BBitmap*
Bookmark::Favicon()
{
	return fFavicon;
}


void
Bookmark::SetTitle(BString *title)
{
	fTitle = new BString(*title);
}


void
Bookmark::SetUrl(BString *url)
{
	fUrl = new BString(*url);
}


void
Bookmark::SetParentDirectory(BDirectory *parentDirectory)
{
	fParentDirectory = new BDirectory(*parentDirectory);
}


void
Bookmark::SetFavicon(BBitmap *favicon)
{
	fFavicon = new BBitmap(favicon->Bounds(), favicon->ColorSpace());
}
