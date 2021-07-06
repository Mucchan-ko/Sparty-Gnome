/**
 * \file ItemWorm.cpp
 *
 * \author Trent Belanger
 */

#include "pch.h"
#include <string>
#include "ItemWorm.h"

using namespace Gdiplus;
using namespace std;


/** Constructor
* \param game The game this item is a member of
* \param image file to load the game from
*/
CItemWorm::CItemWorm(CGame* game, const std::wstring image) : CItem(game, image)
{

}

/** Handle updates for animation (makes the worm move)
* \param elapsed The time since the last update
*/
void CItemWorm::Update(double elapsed)
{
    SetLocation(GetX(), GetY() + mWormSpeed * elapsed);
}

/** Game over in event of collision with worm
* \returns None
*/
void CItemWorm::Collision()
{
    GetGame()->GameOver();
}
