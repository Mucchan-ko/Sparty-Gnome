/**
 * \file ItemWall.h
 *
 * \author Trent Belanger
 *
 * Class that implements a Wall
 */

#pragma once
#include <memory>
#include "ItemObstacle.h"
#include <string>

/**
 * Implements a wall item
 */
class CItemWall : public CItemObstacle
{

public:

    CItemWall(CGame* game, const std::wstring image, int width=0, int height=0);

    /// Default constructor (disabled)
    CItemWall() = delete;

    /// Copy constructor (disabled)
    CItemWall(const CItemWall&) = delete;

    /// Draw this item
    void Draw(Gdiplus::Graphics* graphics);
};