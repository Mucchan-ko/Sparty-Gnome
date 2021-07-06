/**
 * \file Money.h
 *
 * \author Xuefeng Sun
 *
 * Class that implements a Money Item
 */

#pragma once
#include <memory>
#include "Item.h"
#include "Game.h"
#include <string>

 /**
  *  Class for the Money Item within the game
  *	 When collected, adds to the players score
  */
class CMoney : public CItem
{

public:

	CMoney(CGame* game, const std::wstring image);

	/// Default constructor (disabled)
	CMoney() = delete;

	/// Copy constructor (disabled)
	CMoney(const CMoney&) = delete;

	void Update(double elapsed) override;

	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node, std::vector<std::wstring>& declaration);

	void Collision();

	/// Get if an item can interact with player
	/// \returns true if item can be interacted with
	bool IsInteractable() { return true; }

private:

	/// Value of the money item when collected
	int mMoneyValue = 100;

	bool mCollided = false; ///< turns true when item is collided with

	int mOriginalX = 0; ///< marks original X location of the money object for displaying the value collected
	int mOriginalY = 0; ///< marks original X location of the money object for displaying the value collected
};

