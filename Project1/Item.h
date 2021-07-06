/**
 * \file Item.h
 *
 * \author Nick Katarzynski
 *
 * Class to implement Item structure
 */


#pragma once
#include "XmlNode.h"
#include <map>
#include <vector>
#include <string>
#include <memory>

using namespace Gdiplus;

class CGame;

/**
 *  Class for all items within the game
 */
class CItem
{
public:
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;

    virtual ~CItem();

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node, std::vector<std::wstring>& declaration);

    /// Handle updates for animation
    /// \param elapsed The time since the last update
    /// \returns None
    virtual void Update(double elapsed){}

    /** The X location of the item
    * \returns X location in pixels */
    virtual double GetX() const { return mX; }

    /** The Y location of the item
    * \returns Y location in pixels */
    virtual double GetY() const { return mY; }

    /// Set the item location
    /// \param x X location
    /// \param y Y location
    /// \returns None
    virtual void SetLocation(double x, double y);

    /// Draw this item
    virtual void Draw(Gdiplus::Graphics* graphics);

    /// Get the width of an item
    /// \returns Item width
    virtual int GetItemWidth() const { return mItemImage->GetWidth(); }

    /// Get the height of an item
    /// \returns Item height
    virtual int GetItemHeight() const { return mItemImage->GetHeight(); }

    /// Get if an item has physical collision
    /// \returns true if item stops gnome
    virtual bool IsPhysical() { return false; }

    /// Get if an item has can be collected
    /// \returns true if item can be collected
    virtual bool IsInteractable() { return false; }

    bool CollisionTest(CItem* item);

    /** getter for current game
     * \
     * \returns mGame */
    CGame* GetGame() { return mGame; }

    /// Set Items image
    /// \param filename name of the file
    /// \returns None
    virtual void SetImage(const std::wstring& filename);

    /// delete this later. for testing
    /// \returns CItem
    CItem* GetThis() { return this;  }

    /// Action on collision with player 
    /// \returns None
    virtual void Collision() {};

    /// Find player object
    /// \returns true if object is player
    virtual bool IsPlayer() { return false;  }

    /// Get Item image
    /// \returns mItemImage
    virtual std::unique_ptr<Gdiplus::Bitmap>& GetImage() { return mItemImage; }

protected:
    //Item constructor
    CItem(CGame* game, const std::wstring& filename);

private:


    CGame* mGame; ///< The game this item is a member of


    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// The image of this item
    std::unique_ptr<Gdiplus::Bitmap> mItemImage;

};

