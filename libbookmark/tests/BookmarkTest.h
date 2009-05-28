#ifndef __BOOKMARKTEST_H
#define __BOOKMARKTEST_H

#include "LeakTracker.h"

#include <cxxtest/TestSuite.h>

#include "Bookmark.h"


class BookmarkTest : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		title = new BString("Bookmark Title");
		url = new BString("http://www.haiku-os.org");
		bookmark = new Bookmark(title, url);
	}

	void tearDown()
	{
		delete bookmark;
		delete url;
		delete title;
		// Make sure there are no memory leaks
		DumpUnfreed();
	}

    void testAccessors()
    {
        TS_ASSERT_EQUALS(title->String(), bookmark->Title()->String());
        TS_ASSERT_EQUALS(url->String(), bookmark->Url()->String());
    }

private:
	BString *title;
	BString *url;
	Bookmark *bookmark;
};


#endif // __BOOKMARKTEST_H

