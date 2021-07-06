/**
 * \file ItemWorm.h
 *
 * \author Trent Belanger
 *
 * Class to implement the worm
 */

#pragma once
#include "Item.h"
#include <memory>
#include <string>
#include "Game.h"

/**
 * Implements a worm item
 */
class CItemWorm : public CItem
{
public:

	CItemWorm(CGame* game, const std::wstring image);

	/// Default constructor (disabled)
	CItemWorm() = delete;

	/// Copy constructor (disabled)
	CItemWorm(const CItemWorm&) = delete;

	void CItemWorm::Update(double elapsed);

	void Collision();

	/// Get if an item can interact with player
	/// \returns true if item can be interacted with
	bool IsInteractable() { return true; }

private:
	int mWormSpeed = -70; ///< speed of the worm
};
