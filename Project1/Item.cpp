/**
 * \file Item.cpp
 *
 * \author Nick Katarzynski
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"
#include <memory>

using namespace std;



/** Constructor
* \param game The game this item is a member of
* \param filename file to load the game from
*/
CItem::CItem(CGame* game, const std::wstring& filename) :
    mGame(game)
{
    mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mItemImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
}


/**
 * Destructor
 */
CItem::~CItem()
{
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * \param node The Xml node we are loading the item from
 * \param declaration
 * \returns None
 */
void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node, vector<wstring>& declaration)
{
    mX = node->GetAttributeDoubleValue(L"x", 0);
    mY = node->GetAttributeDoubleValue(L"y", 0);
}

void CItem::SetLocation(double x, double y)
{
    mX = x;
    mY = y;
}

/**
 * Draw our item
 * \param graphics The graphics context to draw on
 * \returns None
 */
void CItem::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    graphics->DrawImage(mItemImage.get(), 
        float(GetX() - wid / 2), float(GetY() - hit / 2),
        (float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
}

/**
 * Tests for collision between items
 * \param item the 2nd item to be tested
 * \returns true if images have collided
 */
bool CItem::CollisionTest(CItem* item)
{
    // Border for the item
    auto itemLeft = item->GetX() - item->GetItemWidth() / 2;
    auto itemRight = item->GetX() + item->GetItemWidth() / 2;
    auto itemTop = item->GetY() - item->GetItemHeight() / 2;
    auto itemBottom = item->GetY() + item->GetItemHeight() / 2;

    // For us
    auto ourLeft = GetX() - GetItemWidth() / 2;
    auto ourRight = GetX() + GetItemWidth() / 2;
    auto ourTop = GetY() - GetItemHeight() / 2;
    auto ourBottom = GetY() + GetItemHeight() / 2;

    // Test for all of the non-collision cases,
    // cases where there is a gap between the two items
    if (ourRight < itemLeft ||  // Completely to the left
        ourLeft > itemRight ||  // Completely to the right
        ourTop > itemBottom ||  // Completely below
        ourBottom < itemTop)    // Completely above
    {
        return false;
    }

    return true;
}

void CItem::SetImage(const std::wstring& filename)
{
    mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
}
