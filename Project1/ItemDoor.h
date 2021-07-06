/**
 * \file ItemDoor.h
 *
 * \author Nick Katarzynski
 *
 * Class that implements door item of game
 */


#pragma once
#include "Item.h"
#include "ItemGnome.h"
#include "Game.h"
#include <memory>
#include <string>

/**
 * Implements a door item
 */
class CItemDoor : public CItem
{
public:
    CItemDoor(CGame* game, const std::wstring image);

    /// Default constructor (disabled)
    CItemDoor() = delete;

    /// Copy constructor (disabled)
    CItemDoor(const CItemDoor&) = delete;

    bool CollisionTest(CItem* item);

    void Collision();

    /// Get if an item can interact with player
    /// \returns true if item can be interacted with
    bool IsInteractable() { return true; }

protected:

private:
    /// Collision distance for the door in pixels
    const double CollisionDistance = 20;

};

