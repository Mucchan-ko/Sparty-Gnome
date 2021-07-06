/**
 * \file Level.cpp
 *
 * \author Paul Schulte
 */

#include "pch.h"
#include "Level.h"

#include "Background.h"
#include "ItemDoor.h"
#include "ItemGnome.h"
#include "ItemObstacle.h"
#include "ItemPlatform.h"
#include "ItemWall.h"
#include "Money.h"
#include "TuitionUp.h"
#include "Villain.h"
#include "ItemWorm.h"

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/**
 * Constructor
 * \param game A ponter to the game this level is associated with.
 * \param filename The filename of the .xml file that this level is loaded from as a wstring.
 */
CLevel::CLevel(CGame* game, wstring& filename)
{
    mGame = game;
    Load(filename);
    mItems;
}

/**
 * Add an item to the level
 * \param item New item to add
 */
void CLevel::Add(shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/**
* Handle a declaration node.
* \param node Pointer to XML node we are handling
* \param declarations Map of vectors with information associated to a given id
*/
void CLevel::XmlDeclaration(const shared_ptr<xmlnode::CXmlNode>& node, map<wstring, vector<wstring>>& declarations)
{
    wstring name = node->GetName();

    if (name == L"background" || name == L"wall" || name == L"tuition-up" || name == L"door" || name == L"villain" || name == L"worm")
    {
        wstring id = node->GetAttributeValue(L"id", L"");
        wstring image = L"images/" + node->GetAttributeValue(L"image", L"");

        declarations[id] = { image };
    }
    else if (name == L"platform")
    {
        wstring id = node->GetAttributeValue(L"id", L"");
        wstring leftImage = L"images/" + node->GetAttributeValue(L"left-image", L"");
        wstring midImage = L"images/" + node->GetAttributeValue(L"mid-image", L"");
        wstring rightImage = L"images/" + node->GetAttributeValue(L"right-image", L"");

        declarations[id] = { leftImage, midImage, rightImage };
    }
    else if (name == L"money")
    {
        wstring id = node->GetAttributeValue(L"id", L"");
        wstring image = L"images/" + node->GetAttributeValue(L"image", L"");
        wstring value = node->GetAttributeValue(L"value", L"");

        declarations[id] = { image, value };
    }
}

/**
* Handle an item node.
* \param node Pointer to XML node we are handling
* \param declarations Map of vectors with information associated to a given id
*/
void CLevel::XmlItem(const shared_ptr<xmlnode::CXmlNode>& node, map<wstring, vector<wstring>>& declarations)
{
    // A pointer for the item we are loading
    vector<shared_ptr<CItem>> items;

    // We have an item. What type?
    wstring name = node->GetName();
    wstring id;

    if (name == L"background")
    {
        id = node->GetAttributeValue(L"id", L"");
        items.push_back(make_shared<CBackground>(mGame, declarations[id][0]));
    }
    else if (name == L"platform")
    {
        id = node->GetAttributeValue(L"id", L"");
        double width = node->GetAttributeDoubleValue(L"width", 0);
        double height = node->GetAttributeDoubleValue(L"height", 0);

        int num = width / 32;

        //items.push_back(make_shared<CItemPlatform>(mGame, declarations[id][1], width, height));

        items.push_back(make_shared<CItemPlatform>(mGame, declarations[id], width, height));

        //items.push_back(make_shared<CItemPlatform>(mGame, declarations[id][1], width, height));
        /*
        if (num < 2)
        {
            items.push_back(make_shared<CItemPlatform>(mGame, declarations[id][1]));
        }
        else
        {
            items.push_back(make_shared<CItemPlatform>(mGame, declarations[id][0]));
            for (int i = 0; i < num - 2; i++)
            {
                items.push_back(make_shared<CItemPlatform>(mGame, declarations[id][1]));
            }
            items.push_back(make_shared<CItemPlatform>(mGame, declarations[id][2]));
        }
        */

        double startPos = (width + 32) / 2;
        wstring val = to_wstring(node->GetAttributeDoubleValue(L"x", 0) + 32 -startPos);
        //node->SetAttribute(L"x", val);
    }
    else if (name == L"wall")
    {
        id = node->GetAttributeValue(L"id", L"");
        double height = node->GetAttributeDoubleValue(L"height", 0);
        double width = node->GetAttributeDoubleValue(L"width", 0);

        int num = height / 32;

        items.push_back(make_shared<CItemWall>(mGame, declarations[id][0], width, height));

        /*
        for (int i = 0; i < num; i++)
        {
            items.push_back(make_shared<CItemWall>(mGame, declarations[id][0]));
        }
        */

        double startPos = (height + 32) / 2;
        wstring val = to_wstring(node->GetAttributeDoubleValue(L"y", 0) - startPos);
        //node->SetAttribute(L"y", val);
    }
    else if (name == L"tuition-up")
    {
        id = node->GetAttributeValue(L"id", L"");
        items.push_back(make_shared<CTuitionUp>(mGame, declarations[id][0]));
    }
    else if (name == L"door")
    {
        id = node->GetAttributeValue(L"id", L"");
        items.push_back(make_shared<CItemDoor>(mGame, declarations[id][0]));
    }
    else if (name == L"villain")
    {
        id = node->GetAttributeValue(L"id", L"");
        items.push_back(make_shared<CVillain>(mGame, declarations[id][0]));
    }
    else if (name == L"money")
    {
        id = node->GetAttributeValue(L"id", L"");
        items.push_back(make_shared<CMoney>(mGame, declarations[id][0]));
    }
    else if (name == L"worm")
    {
        id = node->GetAttributeValue(L"id", L"");
        items.push_back(make_shared<CItemWorm>(mGame, declarations[id][0]));
    }

    for (auto item : items)
    {
        /*
        if (name == L"platform")
        {
            wstring val = to_wstring(node->GetAttributeDoubleValue(L"x", 0) + 32);
            node->SetAttribute(L"x", val);
        }
        
        else if (name == L"wall")
        {
            wstring val = to_wstring(node->GetAttributeDoubleValue(L"y", 0) + 32);
            node->SetAttribute(L"y", val);
        }
        */

        if (name == L"background")
        {
            if (mBackCount >= 1)
            {
                wstring val = to_wstring(node->GetAttributeDoubleValue(L"x", 0)-mBackCount*1.75);
                node->SetAttribute(L"x", val);
            }
            mBackCount += 1;
        }

        if (item != nullptr)
        {
            item->XmlLoad(node, declarations[id]);
            Add(item);
        }
    }
}

/**
 * Load the level from an XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * \param filename The filename of the file to load the level from.
 */
void CLevel::Load(const wstring& filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Load the initial level values
        mWidth = root->GetAttributeDoubleValue(L"width", 0);
        mHeight = root->GetAttributeDoubleValue(L"height", 0);
        mStartY = root->GetAttributeDoubleValue(L"start-y", 0);
        mStartX = root->GetAttributeDoubleValue(L"start-x", 0);

        mGame->SetStartPos(int(mStartX), int(mStartY));

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //

        // Stores the provided declarations for later reference when loading items
        map<wstring, vector<wstring>> declarations;
        
        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"declarations")
            {
                for (auto dec : node->GetChildren())
                {
                    XmlDeclaration(dec, declarations);
                }
            }
        }

        for (auto node : root->GetChildren())
        {
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"items")
            {
                for (auto dec : node->GetChildren())
                {
                    XmlItem(dec, declarations);
                }
            }
        }
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
}

/**
 * Sets the start position of the game this level is associated with.
 * \param filename The filename of the .xml file that this level is loaded from as a wstring.
 */
void CLevel::SetGameStart(const wstring& filename)
{
    shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

    auto startY = root->GetAttributeDoubleValue(L"start-y", 0);
    auto startX = root->GetAttributeDoubleValue(L"start-x", 0);

    mGame->SetStartPos(int(startX), int(startY));
}
