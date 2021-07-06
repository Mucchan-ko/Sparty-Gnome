#include "pch.h"
#include "CppUnitTest.h"

#include "level.h"
#include "Background.h"
#include "ItemDoor.h"
#include "ItemGnome.h"
#include "ItemObstacle.h"
#include "ItemPlatform.h"
#include "ItemWall.h"
#include "Money.h"
#include "TuitionUp.h"
#include "Villain.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CLevelTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestConstructor)
		{
			CGame game;
			wstring path = L"levels/level0.xml";
			CLevel level0 = CLevel(&game, path);

			// Test that all items were loaded
			Assert::AreEqual(level0.GetItems().size(), 8, 0.0);

			path = L"levels/level1.xml";
			CLevel level1 = CLevel(&game, path);
		}

	};
}