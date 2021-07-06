/**
 * \file ItemWall.cpp
 *
 * \author Trent Belanger
 */
#include "pch.h"
#include <string>
#include "ItemWall.h"

using namespace Gdiplus;
using namespace std;

/** Constructor
 * \param game game this object is a part of
 * \param image file to load the item image from
 * \param width width of wall object
 * \param height height of wall object
*/
CItemWall::CItemWall(CGame* game, const std::wstring image, int width, int height)
    : CItemObstacle(game, image, width, height)
{

}

/**
 * Draw our item
 * \param graphics The graphics context to draw on
 */
void CItemWall::Draw(Gdiplus::Graphics* graphics)
{
    int y = GetY() - mHeight / 2;

    while (y < GetY() + mHeight / 2)
    {
        graphics->DrawImage(CItem::GetImage().get(),
            float(GetX() - CItem::GetImage()->GetWidth() / 2), float(y),
            (float)CItem::GetImage()->GetWidth(), (float)CItem::GetImage()->GetHeight());

        y += 32;
    }
}