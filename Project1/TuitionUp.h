/**
 * \file TuitionUp.h
 *
 * \author Xuefeng Sun
 *
 * Class that implements an TuitionUp Item
 */

#pragma once
#include <memory>
#include "Item.h"
#include "Game.h"

#include <string>

 /**
  *  Class for the TuitionUp Item within the game
  *	 When collected, changes the tuition multiplier
  */
class CTuitionUp : public CItem
{

public:

	CTuitionUp(CGame* game, const std::wstring image);

	/// Default constructor (disabled)
	CTuitionUp() = delete;

	/// Copy constructor (disabled)
	CTuitionUp(const CTuitionUp&) = delete;

	void Update(double elapsed) override;


	void Collision();

	/// Get if an item can interact with player
	/// \returns true if item can be interacted with
	bool IsInteractable() { return true; }

private:
	bool mCollided = false; ///< turns true when item is collided with
	
	int mNewY = 0; ///< used for displaying the "Tuition Up!" text
	int mFontSize = 30; ///< font size of the "Tuition Up!" text
};

