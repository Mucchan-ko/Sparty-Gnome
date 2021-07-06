/**
 * \file ItemDoor.cpp
 *
 * \author Nick Katarzynski
 */


#include "pch.h"
#include "ItemDoor.h"

using namespace Gdiplus;
using namespace std;


/// Image filename
const wstring ItemDoorImageName = L"images/door.png";

/** Constructor
* \param game The game this item is a member of
* \param image file to load the item image from
*/
CItemDoor::CItemDoor(CGame* game, const std::wstring image) : CItem(game, ItemDoorImageName)
{

}

/**
 * Checks if player is colliding with door
 * \param item Item that door is colliding with
 * \returns true if items are within 20 pixels
 */
bool CItemDoor::CollisionTest(CItem* item)
{
    // Collision for door is different
    double dx = item->GetX() - GetX();
    double dy = item->GetY() - GetY();
    double distance = sqrt(dx * dx + dy * dy);
    if (distance < CollisionDistance)
    {
        return true;
    }

    return false;
}

/** Player enters the next level upon collision.
* \returns None
*/
void CItemDoor::Collision()
{
    GetGame()->NextLevel();
}
