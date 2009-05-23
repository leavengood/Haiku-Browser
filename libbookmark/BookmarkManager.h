// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
//  Copyright 2009 Haiku Inc. All rights reserved.
//  Distributed under the terms of the MIT License.
//
//  Author:
// 			Maxime Simon, simon.maxime (at) gmail.com
// 
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#ifndef BOOKMARK_MANAGER_H
#define BOOKMARK_MANAGER_H


#include <List.h>
#include <Menu.h>

#include "Bookmark.h"

class BookmarkManager {
	public:
		BookmarkManager(BDirectory *directory = NULL);
		~BookmarkManager();

		void	AddBookmark(Bookmark *bookmark);
		void	ManageBookmarks();
		BList*	GetBookmarkList(BDirectory *directory);
		void	BuildBookmarkMenu(BMenu *menu, BDirectory *directory = NULL,
			bool recursively = true);

	private:
		BDirectory	*fBookmarksDirectory;
};

#endif // BOOKMARK_MANAGER_H
