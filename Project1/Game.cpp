/**
 * \file Game.cpp
 *
 * \author Trent Belanger
 */

#include <algorithm>
#include "pch.h"
#include "Game.h"
#include "Item.h"
#include "Level.h"
#include <string>
#include <algorithm>

using namespace Gdiplus;
using namespace std;


/**
* Game constructor
*/
CGame::CGame()
{
    wstring path = L"levels/level0.xml";
    shared_ptr<CLevel> level0 = make_shared<CLevel>(this, path);
    AddLevel(level0);

    path = L"levels/level1.xml";
    shared_ptr<CLevel> level1 = make_shared<CLevel>(this, path);
    AddLevel(level1);

    path = L"levels/level2.xml";
    shared_ptr<CLevel> level2 = make_shared<CLevel>(this, path);
    AddLevel(level2);

    path = L"levels/level3.xml";
    shared_ptr<CLevel> level3 = make_shared<CLevel>(this, path);
    AddLevel(level3);

    Load(1);
}

/**
 * Destructor
 */
CGame::~CGame() {

}

/**
 * Draw the game area
 * \param width Width of the client window
 * \param height Height of the client window
 */
void CGame::OnDraw(int width, int height)
{
    //
    // Automatic Scaling
    //
    mScale = float(height) / float(Height);
    graphics->ScaleTransform(mScale, mScale);

    // Determine the virtual width
    auto virtualWidth = (float)width / mScale;

    // Determine the virtual height
    auto virtualHeight = (float)height / mScale;

    // Compute the amount to scroll in the X dimension
    auto xOffset = (float)-mGnome->GetX() + virtualWidth / 2.0f;

    // Compute the amount to scroll in the Y dimension
    auto yOffset = (float)-mGnome->GetY() + virtualHeight / 2.0f;

    mxOffset = xOffset;
    myOffset = yOffset;

    auto save = graphics->Save();

    if (mCurrentLevel != 3)
        graphics->TranslateTransform(xOffset, 0);
    else
        graphics->TranslateTransform(0, yOffset);

    // Anything drawn here will have xOffset added to every X location

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
    mGnome->Draw(graphics);

    graphics->Restore(save);

    DisplayTime();
    DisplayScore();
    DisplayMessage();
}

/**
 * Add an item to the Game
 * \param item New item to add
 */
void CGame::Add(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/**
* Removes an item from the Game
* \param item item to delete
*/
void CGame::Delete(std::shared_ptr<CItem> item)
{
    auto loc = find(::begin(mItems), ::end(mItems), item);
    if (loc != ::end(mItems))
    {
        mItems.erase(loc);
    }
}

/**
* Removes an item from the Game by reference
* \param item item to delete
*/
void CGame::Delete(CItem* item)
{
}

/**
 * Displays a message on the middle of the screen.
 */
void CGame::DisplayMessage()
{

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 142);

    SolidBrush pink(Color(255, 192, 203));

    if (mTime >= 0 && mTime < 4) 
    {
        string level = "Level " + to_string(mCurrentLevel) + " Start";
        std::wstring name = std::wstring(level.begin(), level.end());
        const wchar_t* test2 = name.c_str();


        graphics->DrawString(test2, -1, &font, PointF(250, 512), &pink);
        mGnome->Halt();

        if (mComplete)
            mComplete = false;
    }
    else if (mTime < 0 && mComplete)
    {
        graphics->DrawString(L"Level Complete!", -1, &font, PointF(100, 512), &pink);
        mGnome->Halt();
        mGnome->SetYVelocity(500);
    }
    else if (mTime < 0)
    {
        graphics->DrawString(L"You Lose!", -1, &font, PointF(512, 512), &pink);
        mGnome->Halt();
        mGnome->SetYVelocity(500);
    }
    else
    {
        graphics->DrawString(L"", -1, &font, PointF(0, 0), &pink);
    }
}

/**
 * Displays the time.
 */
void CGame::DisplayTime()
{
    string test = "0:00";
    int minutes = floor(mTime / 60);
    int seconds = (int(mTime) % 10);
    int seconds2 = (int(floor(mTime / 10)) % 6);
    if (mTime < 0)
        test = "0:00";
    else
        test = to_string(minutes) + ":" + to_string(seconds2) + to_string(seconds);
    std::wstring name = std::wstring(test.begin(), test.end());
    const wchar_t* test2 = name.c_str();

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 76);

    SolidBrush cyan(Color(60, 255, 255));
    graphics->DrawString(test2, -1, &font, PointF(2, 2), &cyan);
}

/**
 * Displays the score.
 */
void CGame::DisplayScore()
{
    string test = "$" + to_string(int(this->GetScore()));
    std::wstring name = std::wstring(test.begin(), test.end());
    const wchar_t* test2 = name.c_str();

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 76);

    SolidBrush cyan(Color(60, 255, 255));
    graphics->DrawString(test2, -1, &font, PointF(1530, 2), &cyan);
}

/**
 * Displays message at the given coordinates
 * \param message to be displayed
 * \param x x coordinate to be displayed at
 * \param y y coordinate to be displayed at
 * \param fontsize size of font to be displayed
 */
void CGame::DisplayItemMessage(const wchar_t* message, int x, int y, int fontsize)
{
    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, fontsize);

    SolidBrush green(Color(0, 255, 60));
    if (graphics != NULL)
    {
        if (mCurrentLevel == 3) {
            graphics->DrawString(message, -1, &font, PointF(x, y + myOffset), &green);
        }
        else {
            graphics->DrawString(message, -1, &font, PointF(x + mxOffset, y), &green);
        }
    }
}


/**
 * Clear the Game data.
 *
 * Deletes all known items in the Game.
 */
void CGame::Clear()
{
    mItems.clear();
    mDisplayList.clear();
}

/**
 * Indicates that player has died in level
 */
void CGame::GameOver()
{
    /*
    this->Clear();
    mScoreboard.Clear();
    Load(mCurrentLevel);
    */
    mTime = -2;
    mGnome->SetCollideable(false);
    //mGnome->Reset(mStartX, mStartY);
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CGame::Update(double elapsed)
{
    if (mTime > -1 && mTime < 0)
    {
        this->Clear();
        mScoreboard.Clear();
        Load(mCurrentLevel);
    }

    mGnome->Update(elapsed);
    for (auto item : mDisplayList)
    {
        item->Update(elapsed);
    }

    mDisplayList = mItems;
    
    mTime += elapsed;
}

/**
 * Returns an item that is colliding with the input.
 * \param object The object that is being tested.
 * \returns Shared pointer to item that is colliding with object.
 */
std::shared_ptr<CItem> CGame::CollisionTest(CItem* object)
{
    for (auto item2 : mDisplayList)
    {
        if (item2->CollisionTest(mGnome->GetThis()) 
            && (item2->IsPhysical())// || item2->IsInteractable())
            && (item2->GetThis() != object))
        {
            return item2;
        }
    }
    return nullptr;
}

/**
 * Loads the given level into the game
 * \param level The level that is to be loaded.
 */
void CGame::Load(int level)
{
    wstring path;

    this->Clear();
    mScoreboard.Clear();
    mTime = 0;
    mCurrentLevel = level;

    if (level == 0)
    {
        path = L"levels/level0.xml";
        shared_ptr<CLevel> level0 = make_shared<CLevel>(this, path);
        mLevels[level] = level0;
    }

    else if (level == 1)
    {
        path = L"levels/level1.xml";
        shared_ptr<CLevel> level1 = make_shared<CLevel>(this, path);
        mLevels[level] = level1;
    }

    else if (level == 2)
    {
        path = L"levels/level2.xml";
        shared_ptr<CLevel> level2 = make_shared<CLevel>(this, path);
        mLevels[level] = level2;
    }

    else if (level == 3)
    {
        path = L"levels/level3.xml";
        shared_ptr<CLevel> level3 = make_shared<CLevel>(this, path);
        mLevels[level] = level3;
    }

    for (auto item : mLevels[level]->GetItems())
    {
        mItems.push_back(item);
    }
    
    mGnome->Reset(mStartX, mStartY);
    mGnome->SetCollideable(true);
    mDisplayList = mItems;
    mLevelHeight = mLevels[level]->GetHeight();
}

/**
 * Adds a level to mLevels
 * \param level The level object to be added.
 */
void CGame::AddLevel(std::shared_ptr<CLevel> level)
{
    mLevels.push_back(level);
}

/**
 * returns player  object
 * \returns mGnome
 */
std::shared_ptr<CItemGnome> CGame::GetGnome()
{
    return mGnome;
}

/**
 * Finds shared_ptr of an item
 * \param item Item to return shared_ptr to
 * \returns shared_ptr from mItems
 */
shared_ptr<CItem> CGame::GetItem(CItem* item)
{
    for (auto object : mItems)
    {
        if (object->GetThis() == item)
            return object;
    }
    return nullptr;
}

/**
 * Returns all items colliding with the gnome.
 * \returns Vector of shared pointers to CItems containing all items colliding with the gnome.
 */
vector<shared_ptr<CItem>> CGame::GetInteracts()
{
    vector<shared_ptr<CItem>> collided;

    for (auto item2 : mDisplayList)
    {
        if (item2->CollisionTest(mGnome->GetThis())
            && item2->IsInteractable())
        {
            collided.push_back(item2);
        }
    }
    return collided;
}

/**
 * Loads the next level.
 * Reloads level 3 if the current level is 3.
 */
void CGame::NextLevel()
{
    if (mCurrentLevel < 3)
    {
        mCurrentLevel++;
    }

    this->Clear();
    this->Load(mCurrentLevel);
    mComplete = true;
    mTime = -2;
}
