/**
 * \file ItemObstacle.h
 *
 * \author Trent Belanger
 *
 * Class that implements an Obstacle Item
 */

#pragma once
#include <memory>
#include "Item.h"
#include <string>

/**
 * Implements an obstacle item
 * This is a base class for the platform and wall items
 */
class CItemObstacle : public CItem
{

public:
    /// Obstacle Constructor
    CItemObstacle(CGame* game, const std::wstring image, int width=0, int height=0);

    /// Default constructor (disabled)
    CItemObstacle() = delete;

    /// Copy constructor (disabled)
    CItemObstacle(const CItemObstacle&) = delete;

    /// Get if an item has physical collision
    /// \returns true if item stops gnome
    bool IsPhysical() override { return true; }

    /// Get the width of an item
    /// \returns Item width
    int GetItemWidth() const { return mWidth; }

    /// Get the height of an item
    /// \returns Item height
    int GetItemHeight() const { return mHeight; }


protected:
    /// Width of obstacle
    int mWidth = 0;

    /// Height of obstacle
    int mHeight = 0;


private:
};

