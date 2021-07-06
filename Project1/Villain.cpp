/**
 * \file Villain.cpp
 *
 * \author Paul Schulte
 */

#include "pch.h"
#include "Villain.h"
#include <string>

using namespace Gdiplus;
using namespace std;


/// Jump speed in virtual pixels per second per second
const double JumpSpeed = 240
;

/// Jump height in virtual pixels
const double JumpHeight = 300;


/** Constructor
* \param game The game this item is a member of
* \param image file to load the game from
*/
CVillain::CVillain(CGame* game, const std::wstring image) : CItem(game, image)
{

}

/**
 * Handle updates in time of our villain
 *
 * This is called before we draw and allows the villain to jump.
 * We add our speed times the amount of time that has elapsed.
 * \param elapsed Time elapsed since the class call
 */
void CVillain::Update(double elapsed)
{
    if (mHeight >= JumpHeight)
    {
        mIsUp = false;
    }
    else if (mHeight <= 0)
    {
        mIsUp = true;
    }

    double oldY = GetY();
    SetLocation(GetX(), GetY() + JumpSpeed * elapsed * (mIsUp ? -1 : 1));

    mHeight += oldY - GetY();
}

/** Tuition Rate changes in the event of a collision
* \returns None
*/
void CVillain::Collision()
{
    GetGame()->GetGnome()->SetCollideable(false);
    GetGame()->GameOver();
}
