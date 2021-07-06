/**
 * \file TuitionUp.cpp
 *
 * \author Xuefeng Sun
 */
#include "pch.h"
#include <string>
#include "TuitionUp.h"



using namespace Gdiplus;
using namespace std;

/// Image filename
const wstring mTuitionUpImage = L"images/stanley.png";

/** Constructor
* \param game The game this item is a member of
* \param image file to load the item image from
*/
CTuitionUp::CTuitionUp(CGame* game, const std::wstring image) : CItem(game, mTuitionUpImage)
{
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CTuitionUp::Update(double elapsed)
{
    if (mCollided == true)
    {
        if (this->GetY() < mNewY + 700)
        {
            this->SetLocation(this->GetX(), this->GetY() + 18);

            string message1 = "Tuition Up!";
            std::wstring name = std::wstring(message1.begin(), message1.end());
            const wchar_t* message = name.c_str();
            GetGame()->DisplayItemMessage(message, this->GetX(), mNewY, mFontSize);

            mNewY -= 1;
            mFontSize += 1;
        }

        else {
            std::shared_ptr<CItem> mColTest = this->GetGame()->GetItem(this);
            GetGame()->Delete(mColTest);
        }

        return;
    }
}

/** Tuition Rate changes in the event of a collision
* \returns None
*/
void CTuitionUp::Collision()
{
    if (mCollided == false)
    {
        CGame* game = GetGame();
        game->SetTuition(game->GetTuitionRate() + 0.1);
        mCollided = true;

        mNewY = this->GetY();
    }

    return;
}