#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "Item.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	/// Test Item filename 
	const std::wstring TestImageName = L"images/gnome.png";

	/** Mock class for testing CItem */
	class CItemMock : public CItem
	{
	public:
		/** Constructor
		 * \param game The game this is a member of */
		CItemMock(CGame* game) :
			CItem(game, TestImageName) {}

		virtual void Draw(Gdiplus::Graphics* graphics) {}
	};

	TEST_CLASS(CItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCItemConstruct)
		{
			CGame game;
			CItemMock item(&game);
		}

		TEST_METHOD(TestCItemLocation)
		{
			CGame game;
			CItemMock item(&game);

			Assert::AreEqual(0, item.GetX(), 0);
			Assert::AreEqual(0, item.GetY(), 0);

			// Test SetLocation, GetX, and GetY
			item.SetLocation(10.5, 17.2);
			Assert::AreEqual(10.5, item.GetX(), 0.0001);
			Assert::AreEqual(17.2, item.GetY(), 0.0001);

			// Test a second with with different values
			item.SetLocation(-72, -107);
			Assert::AreEqual(-72, item.GetX(), 0.0001);
			Assert::AreEqual(-107, item.GetY(), 0.0001);
		}

		TEST_METHOD(TestCItemCollision)
		{
			CGame game;
			CItemMock item1(&game);
			CItemMock item2(&game);

			// Give items same location
			item1.SetLocation(10, 10);
			item2.SetLocation(10, 10);

			Assert::IsTrue(item1.CollisionTest(&item1));
			Assert::IsTrue(item1.CollisionTest(&item2));

			// change items to different locations
			item1.SetLocation(0, 0);
			item2.SetLocation(1000, 1000);

			Assert::IsFalse(item1.CollisionTest(&item2));
		}

	};
}