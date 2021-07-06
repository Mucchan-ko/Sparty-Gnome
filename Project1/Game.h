/**
 * \file Game.h
 *
 * \author Trent Belanger
 *
 * Class that implements the game.
 *
 *
 */

#pragma once
#include<memory>
#include<vector>
#include<string>
#include "XmlNode.h"
#include "ItemGnome.h"

class CItem;
class CLevel;

/**
 * Implements a game
 */
class CGame
{
public:
    CGame();
    virtual ~CGame();

    void OnDraw(int height, int width);
    void Add(std::shared_ptr<CItem> item);
    void Delete(std::shared_ptr<CItem> item);
    void Load(int level);
    void AddLevel(std::shared_ptr<CLevel> level);
    void Update(double elapsed);
    void Clear();
    void GameOver();
    void Delete(CItem* item);
    void DisplayMessage();
    void DisplayTime();
    void DisplayScore();
    void DisplayItemMessage(const wchar_t* message, int x, int y, int fontsize);
    void NextLevel();
    std::shared_ptr<CItem> CollisionTest(CItem* object = nullptr);
    std::shared_ptr<CItem> GetItem(CItem* item);
    std::shared_ptr<CItemGnome> GetGnome();
    std::vector<std::shared_ptr<CItem>> GetInteracts();

    /// Get the current score.
    /// \returns The current score as a double.
    double GetScore() { return mScoreboard.GetScore(); }

    /// Sets the current score.
    /// \param score The value to set the score to as a double.
    void SetScore(double score) { mScoreboard.SetScore(score); }

    /// Gets the current tuition rate.
    /// \returns The current tuition rate as a double.
    double GetTuitionRate() { return mScoreboard.GetTuitionRate(); }

    /// Sets the tuition rate.
    /// \param rate The value to set the rate to as a double.
    void SetTuition(double rate) { mScoreboard.SetTuition(rate); }

    /// Sets the starting position.
    /// \param x The x component of the starting position as an int.
    /// \param y The y component of the starting position as an int.
    void SetStartPos(int x, int y) { mStartX = x; mStartY = y; }

    /// Sets the graphics of the game.
    /// \param g1 A pointer to the Gdiplus graphics to be used.
    void setGraphics(Gdiplus::Graphics* g1) { graphics = g1; }

    /// Gets the height of the level.
    /// \returns The height of the level as a double.
    double GetHeight() { return mLevelHeight; }

    /// Get the current time
    /// \returns The current time as a double.
    double GetTime() { return mTime; }

    /// Gets the starting position.
    /// \returns int vector containing x and y start position
    std::vector<int> GetStartPos() 
    { 
        std::vector<int> pos;
        pos.push_back(mStartX);
        pos.push_back(mStartY);
        return pos;
    }

    /**
     * Scoreboard class.
     */
    class Scoreboard
    {
    public:

        /** Constructor
        * \param game The game we are iterating over */
        Scoreboard(CGame* game) : mGame(game) {}

        /**
         * Returns score of game
         * \returns mScore
         */
        double GetScore() { return mScore; }

        /// Sets the current score.
        /// \param score The value to set the score to as a double.
        void SetScore(double score) { mScore = score; }

        /// Sets the tuition rate.
        /// \param rate The value to set the rate to as a double.
        void SetTuition(double rate) { mTuitionRate = rate; }

        
        /// Gets the current tuition rate.
        /// \returns The current tuition rate as a double.
        double GetTuitionRate() { return mTuitionRate; }

        /// Resets all scoreboard menus
        void Clear()
        {
            mScore = 0;
            mTuitionRate = 1;
        }

    private:
        /// Collection to iterate over
        CGame* mGame;

        /// Player score
        double mScore = 0;

        /// Money Tuition Rate
        double mTuitionRate = 1;
    };

private:
    /// Scoreboard of game
    Scoreboard mScoreboard = Scoreboard(this);

    /// Player character
    std::shared_ptr<CItemGnome> mGnome = std::make_shared<CItemGnome>(this);

    /// All of the items to populate our game
    std::vector<std::shared_ptr<CItem> > mItems;

    /// Item vector we can do operations on
    std::vector<std::shared_ptr<CItem> > mDisplayList;

    /// Gnome Start X position
    int mStartX = 0;

    /// Gnome Start Y position
    int mStartY = 0;

    /// Game area height in virtual pixels
    const static int Height = 1024;

    /// Scale of game
    float mScale = 0;

    /// time of game
    double mTime = 0;

    /// List of levels in the game
    std::vector<std::shared_ptr<CLevel>> mLevels;

    /// Current level
    int mCurrentLevel = 0;

    /// graphics object
    Gdiplus::Graphics* graphics;

    /// Compute the amount to scroll in the X dimension
    float mxOffset;

    /// Compute the amount to scroll in the Y dimension
    float myOffset;

    /// Height of current level
    double mLevelHeight;

    /// If user has completed a level
    bool mComplete = false;
};
