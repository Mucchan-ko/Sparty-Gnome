#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "ItemGnome.h"
#include "Money.h"
#include "ItemWall.h"
#include "ItemPlatform.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const wstring MoneyImage = L"images/money100.png";

namespace Testing
{
	TEST_CLASS(CItemGnomeTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestGnomeCollision)
		{
			CGame game;

			shared_ptr<CMoney> itemMoney = make_shared<CMoney>(&game, MoneyImage);
			itemMoney->SetLocation(100, 150);
			//game.Add(itemMoney);

			shared_ptr<CItemWall> itemPlatform = make_shared<CItemWall>(&game, MoneyImage);
			itemPlatform->SetLocation(100, 200);
			//game.Add(itemPlatform);

			shared_ptr<CItemGnome> itemGnome = make_shared<CItemGnome>(&game);
			itemGnome->SetLocation(1120, 112);
			//game.Add(itemGnome);

			auto test = game.CollisionTest();
			Assert::IsTrue(test != itemMoney);
			itemMoney->SetLocation(852, 570);
			game.GetGnome()->SetLocation(1024,112);
			game.Load(0);
			game.Update(1);
			Assert::AreEqual(game.GetScore(), 100, 0.0001);
		}

	};
}