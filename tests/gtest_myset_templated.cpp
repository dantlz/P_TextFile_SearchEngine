#include <iostream>
#include <cstdlib>
#include <sstream>
#include "gtest/gtest.h"

// Include student's solution for the templated version of 'myset.cpp'
#include "myset.h"		

#define RUN_WEB_PAGE 1

#if RUN_WEB_PAGE
	#include "webpage.h"
#endif

// Change following two lines as desired. 
// Replace 'myset' with student's templated class name (if different)
typedef myset<std::string> MySetString;
typedef myset<WebPage *> MySetWebPage;

class MySetTest : public testing::Test
{
	protected:
		MySetTest() { }
		~MySetTest() { }

		virtual void SetUp() 
		{

		}

		virtual void TearDown() 
		{
			
		}

		void DeleteWebPages(MySetWebPage webPageSet)
		{
			for(MySetWebPage::iterator it = webPageSet.begin(); it != webPageSet.end(); ++it)
			{
				delete *it;
			}
			webPageSet.clear();
		}
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(MySetTest, StringUnionEmpty_01)
{
	MySetString set1, set2;
	MySetString set3 = set1.set_union(set2);

	EXPECT_TRUE(set3.empty());
}

TEST_F(MySetTest, StringIntersectionEmpty_02)
{
	MySetString set1, set2;
	MySetString set3 = set1.set_intersection(set2);

	EXPECT_TRUE(set3.empty());
}

TEST_F(MySetTest, StringUnionSingleElement_03)
{
	MySetString set1, set2;
	set1.insert("Hello");
	set2.insert("World");
	MySetString set3 = set1.set_union(set2);

	ASSERT_EQ(set3.size(), 2);

	EXPECT_NE(set3.find("Hello"), set3.end());
	EXPECT_NE(set3.find("World"), set3.end());
}

TEST_F(MySetTest, StringIntersectionSingleElement_04)
{
	MySetString set1, set2;
	set1.insert("Hello");
	set2.insert("Hello");
	MySetString set3 = set1.set_intersection(set2);

	ASSERT_EQ(set3.size(), 1);

	EXPECT_NE(set3.find("Hello"), set3.end());
}

TEST_F(MySetTest, StringUnionMultipleElementsNoOverlap_05)
{
	MySetString set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		set1.insert(std::to_string(i));
		set2.insert(std::to_string(i + NUMBER_OF_ELEMENTS));
	}

	MySetString set3 = set1.set_union(set2);

	ASSERT_EQ(set3.size(), 20);

	for(int i = 0; i < 2 * NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_NE(set3.find(std::to_string(i)), set3.end());
	}
}

TEST_F(MySetTest, StringIntersectionMultipleElementsAllDuplicates_06)
{
	MySetString set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		set1.insert(std::to_string(i));
		set2.insert(std::to_string(i));
	}

	MySetString set3 = set1.set_intersection(set2);

	ASSERT_EQ(set3.size(), 10);

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_NE(set3.find(std::to_string(i)), set3.end());
	}
}

TEST_F(MySetTest, StringUnionMultipleElementsPartialOverlap_07)
{
	MySetString set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		set1.insert(std::to_string(i));
		set2.insert(std::to_string(i + NUMBER_OF_ELEMENTS / 2));
	}

	MySetString set3 = set1.set_union(set2);

	ASSERT_EQ(set3.size(), 15);

	for(int i = 0; i < 3 * NUMBER_OF_ELEMENTS / 2; ++i)
	{
		EXPECT_NE(set3.find(std::to_string(i)), set3.end());
	}
}

TEST_F(MySetTest, StringIntersectionMultipleElementsPartialDuplicates_08)
{
	MySetString set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		set1.insert(std::to_string(i));
		set2.insert(std::to_string(i + NUMBER_OF_ELEMENTS / 2));
	}

	MySetString set3 = set1.set_intersection(set2);

	ASSERT_EQ(set3.size(), 5);

	for(int i = NUMBER_OF_ELEMENTS / 2; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_NE(set3.find(std::to_string(i)), set3.end());
	}
}

TEST_F(MySetTest, StringUnionMultipleElementsAllOverlap_09)
{
	MySetString set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		set1.insert(std::to_string(i));
		set2.insert(std::to_string(i));
	}

	MySetString set3 = set1.set_union(set2);

	ASSERT_EQ(set3.size(), 10);

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_NE(set3.find(std::to_string(i)), set3.end());
	}
}

TEST_F(MySetTest, StringIntersectionMultipleElementsNoDuplicates_10)
{
	MySetString set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		set1.insert(std::to_string(i));
		set2.insert(std::to_string(i + NUMBER_OF_ELEMENTS));
	}

	MySetString set3 = set1.set_intersection(set2);

	ASSERT_EQ(set3.size(), 0);
}

#if RUN_WEB_PAGE

TEST_F(MySetTest, WebPageUnionEmpty_11)
{
	MySetWebPage set1, set2;
	MySetWebPage set3 = set1.set_union(set2);

	EXPECT_TRUE(set3.empty());
}

TEST_F(MySetTest, WebPageIntersectionEmpty_12)
{
	MySetWebPage set1, set2;
	MySetWebPage set3 = set1.set_intersection(set2);

	EXPECT_TRUE(set3.empty());
}

TEST_F(MySetTest, WebPageUnionSingleElement_13)
{
	MySetWebPage set1, set2;
	set1.insert(new WebPage("Hello"));
	set2.insert(new WebPage("World"));
	MySetWebPage set3 = set1.set_union(set2);

	ASSERT_EQ(set3.size(), 2);

	for(MySetWebPage::iterator it = set3.begin(); it != set3.end(); ++it)
	{
		std::string fileName = (*it)->filename();
		bool fileNameMatch = fileName == "Hello" || fileName == "World";
		EXPECT_TRUE(fileNameMatch);
	}

	DeleteWebPages(set3);
}


TEST_F(MySetTest, WebPageIntersectionSingleElement_14)
{
	MySetWebPage set1, set2;
	WebPage *webPage = new WebPage("Hello");
	set1.insert(webPage);
	set2.insert(webPage);
	MySetWebPage set3 = set1.set_intersection(set2);

	ASSERT_EQ(set3.size(), 1);

	for(MySetWebPage::iterator it = set3.begin(); it != set3.end(); ++it)
	{
		std::string fileName = (*it)->filename();
		bool fileNameMatch = fileName == "Hello";
		EXPECT_TRUE(fileNameMatch);
	}

	DeleteWebPages(set3);
}

TEST_F(MySetTest, WebPageUnionMultipleElementsNoOverlap_15)
{
	MySetWebPage set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	std::set<int> intSet;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		intSet.insert(i);
		set1.insert(new WebPage(std::to_string(i)));
		set2.insert(new WebPage(std::to_string(i + NUMBER_OF_ELEMENTS)));
	}

	MySetWebPage set3 = set1.set_union(set2);

	ASSERT_EQ(set3.size(), 20);

	for(MySetWebPage::iterator it = set3.begin(); it != set3.end(); ++it)
	{
		std::string fileName = (*it)->filename();
		std::stringstream ss(fileName);
		int fileNumber;
		ss >> fileNumber;
		EXPECT_LE(fileNumber, 19);
		EXPECT_GE(fileNumber, 0);
		intSet.erase(fileNumber);
	}

	EXPECT_TRUE(intSet.empty());

	DeleteWebPages(set3);
}

TEST_F(MySetTest, WebPageIntersectionMultipleElementsAllDuplicates_16)
{
	MySetWebPage set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	std::set<int> intSet;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		intSet.insert(i);
		WebPage *webPage = new WebPage(std::to_string(i));
		set1.insert(webPage);
		set2.insert(webPage);
	}

	MySetWebPage set3 = set1.set_intersection(set2);

	ASSERT_EQ(set3.size(), 10);

	for(MySetWebPage::iterator it = set3.begin(); it != set3.end(); ++it)
	{
		std::string fileName = (*it)->filename();
		std::stringstream ss(fileName);
		int fileNumber;
		ss >> fileNumber;
		EXPECT_LE(fileNumber, 19);
		EXPECT_GE(fileNumber, 0);
		intSet.erase(fileNumber);
	}

	EXPECT_TRUE(intSet.empty());

	DeleteWebPages(set3);
}

TEST_F(MySetTest, WebPageUnionMultipleElementsPartialOverlap_17)
{
	MySetWebPage set1, set2;
	const int NUMBER_OF_ELEMENTS = 20;
	std::set<int> intSet;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		intSet.insert(i);
		WebPage *webPage = new WebPage(std::to_string(i));
		if(i < 5)
		{
			set1.insert(webPage);
		}
		else if(i >15)
		{
			set2.insert(webPage);
		}
		else
		{
			set1.insert(webPage);
			set2.insert(webPage);
		}
	}

	MySetWebPage set3 = set1.set_union(set2);

	ASSERT_EQ(set3.size(), 20);

	for(MySetWebPage::iterator it = set3.begin(); it != set3.end(); ++it)
	{
		std::string fileName = (*it)->filename();
		std::stringstream ss(fileName);
		int fileNumber;
		ss >> fileNumber;
		EXPECT_LE(fileNumber, 20);
		EXPECT_GE(fileNumber, 0);
		intSet.erase(fileNumber);
	}

	EXPECT_TRUE(intSet.empty());

	DeleteWebPages(set3);
}

TEST_F(MySetTest, WebPageIntersectionMultipleElementsPartialDuplicates_18)
{
	MySetWebPage set1, set2;
	const int NUMBER_OF_ELEMENTS = 20;
	std::set<int> intSet;
	MySetWebPage set4;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		WebPage *webPage = new WebPage(std::to_string(i));
		if(i < 6)
		{
			set1.insert(webPage);
		}
		else if(i > 15)
		{
			set2.insert(webPage);
		}
		else
		{
			intSet.insert(i);
			set1.insert(webPage);
			set2.insert(webPage);
		}
		set4.insert(webPage);
	}

	MySetWebPage set3 = set1.set_intersection(set2);

	ASSERT_EQ(set3.size(), 10);

	for(MySetWebPage::iterator it = set3.begin(); it != set3.end(); ++it)
	{
		std::string fileName = (*it)->filename();
		std::stringstream ss(fileName);
		int fileNumber;
		ss >> fileNumber;
		EXPECT_LE(fileNumber, 15);
		EXPECT_GE(fileNumber, 5);
		intSet.erase(fileNumber);
	}

	EXPECT_TRUE(intSet.empty());

	DeleteWebPages(set4);
}

TEST_F(MySetTest, WebPageUnionMultipleElementsAllOverlap_19)
{
	MySetWebPage set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	std::set<int> intSet;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		intSet.insert(i);
		WebPage *webPage = new WebPage(std::to_string(i));
		set1.insert(webPage);
		set2.insert(webPage);
	}

	MySetWebPage set3 = set1.set_union(set2);

	ASSERT_EQ(set3.size(), 10);

	for(MySetWebPage::iterator it = set3.begin(); it != set3.end(); ++it)
	{
		std::string fileName = (*it)->filename();
		std::stringstream ss(fileName);
		int fileNumber;
		ss >> fileNumber;
		EXPECT_LE(fileNumber, 10);
		EXPECT_GE(fileNumber, 0);
		intSet.erase(fileNumber);
	}

	EXPECT_TRUE(intSet.empty());

	DeleteWebPages(set3);
}

TEST_F(MySetTest, WebPageIntersectionMultipleElementsNoDuplicates_20)
{
	MySetWebPage set1, set2;
	const int NUMBER_OF_ELEMENTS = 10;
	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		set1.insert(new WebPage(std::to_string(i)));
		set2.insert(new WebPage(std::to_string(i + NUMBER_OF_ELEMENTS)));
	}

	MySetWebPage set3 = set1.set_intersection(set2);

	ASSERT_EQ(set3.size(), 0);

	DeleteWebPages(set1);
	DeleteWebPages(set2);
}

#endif
