#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "Item.h"
#include "TuitionUp.h"
#include "ItemGnome.h"
#include "Money.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const wstring MoneyImage = L"images/money100.png";
const wstring TuitionUpImage = L"images/stanley.png";

namespace Testing
{
	TEST_CLASS(CMoneyTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestMoneyConstruct)
		{
			CGame game;
			wstring image = L"images/money100.png";
			shared_ptr<CMoney> item = make_shared<CMoney>(&game, image);

		}
		TEST_METHOD(TestMoneyCollision)
		{
			CGame game;

			// test initial values
			Assert::AreEqual(game.GetScore(), 0, 0.0001);
			Assert::AreEqual(game.GetTuitionRate(), 1, 0.0001);

			// test with 100$
			shared_ptr<CMoney> money1 = make_shared<CMoney>(&game, MoneyImage);
			money1->Collision();
			Assert::AreEqual(game.GetScore(), 100, 0.0001);

			game.SetScore(0);

			// test with different tuition rate
			game.SetTuition(1.1);
			shared_ptr<CMoney> money2 = make_shared<CMoney>(&game, MoneyImage);
			money2->Collision();
			Assert::AreEqual(game.GetScore(), 110, 0.0001);
		}	

		TEST_METHOD(TestTuitionHit)
		{
			CGame game;
			game.Load(0);

			// test initial values
			Assert::AreEqual(game.GetScore(), 0, 0.0001);
			Assert::AreEqual(game.GetTuitionRate(), 1, 0.0001);

			shared_ptr<CItemGnome> itemGnome = make_shared<CItemGnome>(&game);
			itemGnome->SetLocation(100, 200);
			game.Add(itemGnome);

			shared_ptr<CTuitionUp> itemTuition = make_shared<CTuitionUp>(&game, TuitionUpImage);
			itemTuition->SetLocation(100, 200);
			game.Add(itemTuition);

			auto test = (game.CollisionTest());
			Assert::IsTrue(test != itemTuition);

			itemTuition->SetLocation(100, 1200);
			//itemGnome->Update(1);
			game.Update(1);
			Assert::AreEqual(game.GetTuitionRate(), 1.1, 0.0001);
		}

	};
}