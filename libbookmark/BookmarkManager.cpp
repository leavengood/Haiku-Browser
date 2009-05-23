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

#include <MenuItem.h>

#include <Roster.h>

#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <typeinfo>

#include "Constants.h"

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


void
BookmarkManager::ManageBookmarks()
{
	BEntry directoryEntry;
	entry_ref directory;

	fBookmarksDirectory->GetEntry(&directoryEntry);
	directoryEntry.GetRef(&directory);

	be_roster->Launch(&directory);
}


BList*
BookmarkManager::GetBookmarkList(BDirectory *directory)
{
	BEntry entry;
	Bookmark *bookmark;
	BList *bookmarkList = new BList(directory->CountEntries());

	directory->Rewind();

	while (directory->GetNextEntry(&entry, false) != B_ENTRY_NOT_FOUND) {
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

			// TODO: Do the same for the favicon, depending on how it will be implemented.

			bookmark = new Bookmark(new BString(titleAttr),
				new BString(urlAttr), directory);
			bookmarkList->AddItem(bookmark);
		}
	}

	return bookmarkList;
}


void
BookmarkManager::BuildBookmarkMenu(BMenu *menu, BDirectory *directory, bool recursively)
{
	if (directory == NULL)
		directory = fBookmarksDirectory;

	BList *bookmarkList = GetBookmarkList(directory);
	BMenuItem *item;

	for (int32 i = 0; i < bookmarkList->CountItems(); i++) {
		Bookmark *bookmark = static_cast<Bookmark*>(bookmarkList->ItemAt(i));

		BMessage *message = new BMessage(kMsgOpenBookmark);
		message->AddString("url", bookmark->Url()->String());

		item = new BMenuItem(bookmark->Title()->String(), message);
		menu->AddItem(item);
	}

	if (recursively) {
		// No bookmark no separator
		if (bookmarkList->CountItems() > 0)
			menu->AddSeparatorItem();

		directory->Rewind();

		BEntry entry;
		int32 nbDirectory = 0;

		while (directory->GetNextEntry(&entry, false) != B_ENTRY_NOT_FOUND) {
			if (entry.IsDirectory()) {
				nbDirectory++;

				char name[B_FILE_NAME_LENGTH];
				entry.GetName(name);

				BMenu *submenu = new BMenu(name);
				BuildBookmarkMenu(submenu, new BDirectory(&entry), true);
				menu->AddItem(submenu);
			}
		}

		// No sub-directory no separator
		if (nbDirectory == 0)
			menu->RemoveItem(bookmarkList->CountItems());
	}
}
