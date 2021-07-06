/**
 * \file ItemObstacle.cpp
 *
 * \author Trent Belanger
 */
#include "pch.h"
#include <string>
#include "ItemObstacle.h"

using namespace Gdiplus;
using namespace std;


/** Constructor
* \param game The game this item is a member of
* \param image file to load the game from
* \param width width of the obstacle
* \param height height of the obstacle
*/
CItemObstacle::CItemObstacle(CGame* game, const std::wstring image, 
    int width, int height) : CItem(game, image)
{
    mWidth = width;
    mHeight = height;
}
