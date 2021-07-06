/**
 * \file ItemPlatform.cpp
 *
 * \author Trent Belanger
 */
#include "pch.h"
#include <string>
#include "ItemPlatform.h"

using namespace Gdiplus;
using namespace std;


/** Constructor
 * \param game game this object is a part of
 * \param declarations vector of wstring image files
 * \param width width of platform object
 * \param height height of platform object
*/
CItemPlatform::CItemPlatform(CGame* game, std::vector<std::wstring> declarations, int width, int height)
    : CItemObstacle(game, declarations[1], width, height)
{
    for (auto image : declarations)
    {
        auto itemImage = unique_ptr<Bitmap>(Bitmap::FromFile(image.c_str()));
        if (itemImage->GetLastStatus() != Ok)
        {
            wstring msg(L"Failed to open ");
            msg += image;
            AfxMessageBox(msg.c_str());
        }
        mImages.push_back(move(itemImage));
    }
}

/**
 * Draw our item
 * \param graphics The graphics context to draw on
 */
void CItemPlatform::Draw(Gdiplus::Graphics* graphics)
{
    // calculate position of leftmost x position
    int x = GetX() - (mWidth / 2);

    // draw left endcap
    graphics->DrawImage(mImages[0].get(),
        float(x), float(GetY() - mImages[0]->GetHeight() / 2),
        (float)mImages[0]->GetWidth(), (float)mImages[0]->GetHeight());

    x += 32;

    // draw middle platform images until right end
    while (x < (GetX() - 32) + (mWidth / 2))
    {
        graphics->DrawImage(mImages[1].get(),
            float(x), float(GetY() - mImages[1]->GetHeight() / 2),
            (float)mImages[1]->GetWidth(), (float)mImages[1]->GetHeight());

        x += 32;
    }

    // draw right endcap
    graphics->DrawImage(mImages[2].get(),
        float(x), float(GetY() - mImages[2]->GetHeight() / 2),
        (float)mImages[2]->GetWidth(), (float)mImages[2]->GetHeight());
}