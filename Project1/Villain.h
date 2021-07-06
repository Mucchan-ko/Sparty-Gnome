/**
 * \file Villain.h
 *
 * \author Paul Schulte
 *
 * Class to implement Villain structure
 */

#pragma once
#include "Item.h"
#include <memory>
#include <string>
#include "Game.h"

/**
 * Implements a villain item
 */
class CVillain : public CItem
{
public:

    CVillain::CVillain(CGame* game, const std::wstring image);

    /// Default constructor (disabled)
    CVillain() = delete;

    /// Copy constructor (disabled)
    CVillain(const CVillain&) = delete;

    void CVillain::Update(double elapsed);

    void Collision();

    /// Get if an item can interact with player
    /// \returns true if item can be interacted with
    bool IsInteractable() { return true; }

private:
    /// height of the villian at a given point
    double mHeight = 0;

    /// determines if villian is moving up or down
    bool mIsUp = true;
};

