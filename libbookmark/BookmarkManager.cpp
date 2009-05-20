// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  Copyright 2009 Haiku Inc. All rights reserved.
//  Distributed under the terms of the MIT License.
//
//  Author:
// 			Maxime Simon, simon.maxime (at) gmail.com
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "BookmarkManager.h"

#include <fs_attr.h>
#include <Entry.h>
#include <File.h>
#include <FindDirectory.h>
#include <NodeInfo.h>
#include <Path.h>

#include <Roster.h>

#include <stdio.h>
#include <string.h>
#include <syslog.h>

BookmarkManager::BookmarkManager(BDirectory *directory)
{
	if (directory == NULL) {
		BPath pathToBookmarks;

		find_directory(B_USER_SETTINGS_DIRECTORY, &pathToBookmarks, true);

		chdir(pathToBookmarks.Path());
		create_directory("bookmarks", 0777);
		pathToBookmarks.Append("bookmarks");

		fBookmarksDirectory = new BDirectory(pathToBookmarks.Path());
	} else
		fBookmarksDirectory = new BDirectory(*directory);
}


BookmarkManager::~BookmarkManager()
{
	delete fBookmarksDirectory;
}


void
BookmarkManager::AddBookmark(Bookmark *bookmark)
{
	BPath bookmarkPath;
	BFile bookmarkFile;
	const char *bookmarkTitle = bookmark->Title()->String();

	if (bookmark->ParentDirectory() != NULL)
		bookmarkPath.SetTo(bookmark->ParentDirectory(), bookmarkTitle);
	else
		bookmarkPath.SetTo(fBookmarksDirectory, bookmarkTitle);

	if (fBookmarksDirectory->CreateFile(bookmarkPath.Path(), &bookmarkFile, true) != B_OK) {
		char str[100];
		sprintf(str, "BookmarkManager: unable to create the bookmark %s", bookmarkTitle);
		syslog(LOG_DEBUG, str);
	}

	BNodeInfo fileInfo(&bookmarkFile);
	fileInfo.SetType("application/x-vnd.Be-bookmark");

	bookmarkFile.WriteAttr("URL", B_STRING_TYPE, 0, bookmark->Url()->String(),
		bookmark->Url()->Length() + 1);
	bookmarkFile.WriteAttr("Title", B_STRING_TYPE, 0, bookmarkTitle,
		bookmark->Title()->Length() + 1);
	// TODO: Add a bitmap attribute for the favicon.
	// We can also use the SetIcon() method of the BNodeInfo class.
}


BList*
BookmarkManager::GetBookmarkList(BDirectory *directory, bool recursively)
{
	BEntry entry;
	Bookmark *bookmark;
	BList *bookmarkList = new BList(directory->CountEntries());

	while (directory->GetNextEntry(&entry, true) != B_ENTRY_NOT_FOUND) {
		BNode node(&entry);
		BNodeInfo nodeInfo(&node);
		char nodeType[B_MIME_TYPE_LENGTH] = { '\0' };

		nodeInfo.GetType(nodeType);

		if (strcmp(nodeType, "application/x-vnd.Be-bookmark") == 0) {
			BFile file(&entry, B_READ_ONLY);
			attr_info attrInfo;
			int32 attrLength;

			// Get the URL attribute of the file
			if (file.GetAttrInfo("URL", &attrInfo) != B_OK)
				syslog(LOG_DEBUG,
					"BookmarkManager::GetBookmarkList, failed to get the bookmark's URL.");

			attrLength = attrInfo.size;

			char urlAttr[attrLength];
			file.ReadAttr("URL", B_STRING_TYPE, 0, urlAttr, attrLength);

			// Get the Title attribute of the file
			if (file.GetAttrInfo("Title", &attrInfo) != B_OK)
				syslog(LOG_DEBUG,
					"BookmarkManager::GetBookmarkList, failed to get the bookmark's Title.");

			attrLength = attrInfo.size;

			char titleAttr[attrLength];
			file.ReadAttr("Title", B_STRING_TYPE, 0, titleAttr, attrLength);

			// TODO: Do the same for the favicon, depending on how it will be implemente.

			bookmark = new Bookmark(new BString(titleAttr),
				new BString(urlAttr), directory);
			bookmarkList->AddItem(bookmark);
		} else if (recursively && entry.IsDirectory()) {
			bookmarkList->AddList(GetBookmarkList(new BDirectory(&entry), true));
		}
	}

	return bookmarkList;
}


void
BookmarkManager::ManageBookmarks()
{
	BEntry directoryEntry;
	entry_ref directory;

	fBookmarksDirectory->GetEntry(&directoryEntry);
	directoryEntry.GetRef(&directory);

	be_roster->Launch(&directory);
}
