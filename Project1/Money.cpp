/**
 * \file Money.cpp
 *
 * \author Xuefeng Sun
 */
#include "pch.h"
#include <string>
#include "Money.h"

using namespace Gdiplus;
using namespace std;


/** Constructor
 * \param game game this object is a part of
 * \param image file to load the item image from
*/
CMoney::CMoney(CGame* game, const std::wstring image) : CItem(game, image)
{
}
 
/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CMoney::Update(double elapsed)
{
    if (mCollided == true)
    {
        if (this->GetY() > mOriginalY-500)
        {
            this->SetLocation(this->GetX(), this->GetY() - 18);

            string message1 = "$" + 
                to_string((int)(mMoneyValue * GetGame()->GetTuitionRate()));
            std::wstring name = std::wstring(message1.begin(), message1.end());
            const wchar_t* message = name.c_str();
            GetGame()->DisplayItemMessage(message, mOriginalX, mOriginalY, 30);
        }

        else
        {
            std::shared_ptr<CItem> mColTest = this->GetGame()->GetItem(this);
            GetGame()->Delete(mColTest);
        }

        return;
    }
}

/** Players score changes upon Collision
* \returns None
*/
void CMoney::Collision()
{
    if (mCollided == false)
    {
        CGame* game = GetGame();
        game->SetScore(game->GetScore() + (mMoneyValue * game->GetTuitionRate()));
        mCollided = true;

        mOriginalX = this->GetX();
        mOriginalY = this->GetY();
    }
}

/** Stores the value of the money
* \param node that stores the money in XML
* \param declaration (value amounts)
*/
void CMoney::XmlLoad(const shared_ptr<xmlnode::CXmlNode>& node, vector<wstring>& declaration)
{
    CItem::XmlLoad(node, declaration);

    mMoneyValue = stoi(declaration[1]);
}
