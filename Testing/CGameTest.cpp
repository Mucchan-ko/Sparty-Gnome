#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "Item.h"
#include "ItemDoor.h"
#include "ItemGnome.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing 
{

	TEST_CLASS(CGameTest) 
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);

		}
		TEST_METHOD(TestCGameConstruct)
		{
			CGame game;
		}

		TEST_METHOD(TestScoreboardScore)
		{
			CGame game;

			// test initial scoreboard values
			Assert::AreEqual(game.GetScore(), 0, 0.0001);

			// test setting scoreboard score
			game.SetScore(100);
			Assert::AreEqual(game.GetScore(), 100, 0.0001);

			// test setting tuition rate
			game.SetTuition(1.1);

		}

		TEST_METHOD(TestScoreboardTuition)
		{
			CGame game;

			// test initial values
			Assert::AreEqual(game.GetScore(), 0, 0.0001);
			Assert::AreEqual(game.GetTuitionRate(), 1, 0.0001);

			// test setters for score, tuition rate
			game.SetTuition(1.1);
			game.SetScore(100);
			Assert::AreEqual(game.GetTuitionRate(), 1.1, 0.0001);
			Assert::AreEqual(game.GetScore(), 100, 0.0001);

			// test resetting scoreboard
			game.GameOver();
			Assert::AreEqual(game.GetScore(), 0, 0.0001);
			Assert::AreEqual(game.GetTuitionRate(), 1, 0.0001);
		}

		TEST_METHOD(TestItemInGame)
		{
			CGame game;

			shared_ptr<CItemGnome> item = make_shared<CItemGnome>(&game);
			item->SetLocation(100, 200);
			game.Add(item);

		}
	};
}