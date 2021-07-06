/**
 * \file Level.h
 *
 * \author Paul Schulte
 *
 * Class that implements a level.
 *
 */
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "XmlNode.h"

class CItem;
class CGame;

/**
 * Implements a level
 */
class CLevel
{
public:
    CLevel(CGame* game, std::wstring& filename);

    void CLevel::Add(std::shared_ptr<CItem> item);
    void CLevel::XmlDeclaration(const std::shared_ptr<xmlnode::CXmlNode>& node, std::map<std::wstring, std::vector<std::wstring>>& declarations);
    void CLevel::XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node, std::map<std::wstring, std::vector<std::wstring>>& declarations);
    void CLevel::Load(const std::wstring& filename);
    void SetGameStart(const std::wstring& filename);

    /// Returns all of the items in the level.
    /// \returns A vector of shared pointers to items.
    std::vector<std::shared_ptr<CItem>> CLevel::GetItems() { return mItems; };

    /// Returns the height of the level.
    /// \returns The height of the level as a double.
    double GetHeight() { return mHeight; }

private:
    /// The game associated with this level
    CGame* mGame;
    /// All of the items in the level
    std::vector<std::shared_ptr<CItem>> mItems;
    /// The width of the level
    double mWidth = 0;
    /// The height of the level
    double mHeight = 0;
    /// The Y position the gnome starts at
    double mStartY = 0;
    /// The X position the gnome starts at
    double mStartX = 0;
    /// Count of background items
    int mBackCount = 0;
};

