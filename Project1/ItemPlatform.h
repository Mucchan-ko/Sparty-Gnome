/**
 * \file ItemPlatform.h
 *
 * \author Trent Belanger
 *
 * Class that implements a Platform
 */

#pragma once
#include <memory>
#include "ItemObstacle.h"
#include <string>
#include <vector>

/**
 * Implements a platform object
 */
class CItemPlatform : public CItemObstacle
{

public:

    CItemPlatform(CGame* game, std::vector<std::wstring> declarations, int width=0, int height=0);

    /// Default constructor (disabled)
    CItemPlatform() = delete;

    /// Copy constructor (disabled)
    CItemPlatform(const CItemPlatform&) = delete;

    /// Draw this item
    void Draw(Gdiplus::Graphics* graphics);

private:
    ///holds all platform images/types
    std::vector<std::unique_ptr<Gdiplus::Bitmap>> mImages;;
};