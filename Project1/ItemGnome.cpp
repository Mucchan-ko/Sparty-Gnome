/**
 * \file ItemGnome.cpp
 *
 * \author Aiden Tang
 */

#include "pch.h"
#include "ItemGnome.h"
#include "Vector.h"
#include "Game.h"

using namespace Gdiplus;
using namespace std;

/// Gravity in virtual pixels per second per second
const double Gravity = 1000;

/// Horizontal character speed in pixels per second
const double HorizontalSpeed = 500.00;

/// Vertical jump speed in pixels per second
const double JumpSpeed = -800;

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.01;

/// base Image filename
const wstring ItemGnomeImage = L"images/gnome.png";

/// sad image filename
const wstring ItemSadGnomeImage = L"images/gnome-sad.png";

/// walk left Image 1 filename
const wstring ItemWalkLeftImage1 = L"images/gnome-walk-left-1.png";

/// walk left Image 2 filename
const wstring ItemWalkLeftImage2 = L"images/gnome-walk-left-2.png";

/// walk right Image 1 filename
const wstring ItemWalkRightImage1 = L"images/gnome-walk-right-1.png";

/// walk right Image 2 filename
const wstring ItemWalkRightImage2 = L"images/gnome-walk-right-2.png";

/// Gnome's image file
auto GnomeImage = ItemGnomeImage;

/** Constructor
* \param game The game this item is a member of
*/
CItemGnome::CItemGnome(CGame* game) : 
    CItem(game, GnomeImage)
{
}

/** Setter
 * \param x position for x direction
 * \param y position for y direction
 */
void CItemGnome::SetLocation(double x, double y) 
{
    mP.SetX(x);
    mP.SetY(y);
}


/** Moves the gnome left
 * \returns None
 */
void CItemGnome::UpdateLeft() 
{
    mV.SetX(-HorizontalSpeed);
}

/** Moves the gnome right
 * \returns None
 */
void CItemGnome::UpdateRight() 
{
    mV.SetX(HorizontalSpeed);
}

/** Makes the gnome jump
 * \returns None
 */
void CItemGnome::UpdateJump() 
{
    SetYVelocity(JumpSpeed);
}

/** Gnome loses X velocity
 * \returns None
 */
void CItemGnome::Stop() 
{
    mV.SetX(0);
}

/** Gnome loses all velocity
 * \returns None
 */
void CItemGnome::Halt()
{
    mV.SetX(0);
    mV.SetY(0);
}

/** Handle updates for animation
* \param elapsed The time since the last update
*/
void CItemGnome::Update(double elapsed)
{
    CItem::Update(elapsed);

    if ((int)GetGame()->GetTime() == 0)
    {
        auto pos = GetGame()->GetStartPos();
        Reset(pos[0], pos[1]);
    }

    // Gravity
    // Compute a new velocity with gravity added in.
    CVector newV(mV.X(), mV.Y() + Gravity * elapsed);

    // Update position
    CVector newP = mP + newV * elapsed;

    //
    // Try updating the Y location. 
    //
    SetLocation(mP.X(), newP.Y());

    auto collided = GetGame()->CollisionTest();
    if (collided != nullptr)
    {
        collided->Collision();

        if (collided->IsPhysical() && mCollideable)
        {
            if (newV.Y() > 0)
            {
                // We are falling, stop at the collision point
                newP.SetY(collided->GetY() - collided->GetItemHeight() / 2 - GetItemHeight() / 2 - Epsilon);
            }
            else
            {
                // We are rising, stop at the collision point
                newP.SetY(collided->GetY() + collided->GetItemHeight() / 2 + GetItemHeight() / 2 + Epsilon);

            }

            // If we collide, we cancel any velocity
            // in the Y direction
            newV.SetY(0);
        }

        
    }

    // 
    // Try updating the X location
    //
    SetLocation(newP.X(), mP.Y());

    auto collided2 = GetGame()->CollisionTest(collided->GetThis());
    if (collided2 != nullptr && collided2 != collided)
    {
        collided2->Collision();
        if (collided2->IsPhysical() && mCollideable)
        {
            if (newV.X() > 0)
            {
                // We are moving to the right, stop at the collision point
                newP.SetX(collided2->GetX() - collided2->GetItemWidth() / 2 - GetItemWidth() / 2 - Epsilon);
            }
            else
            {
                // We are moving to the left, stop at the collision point
                newP.SetX(collided2->GetX() + collided2->GetItemWidth() / 2 + GetItemWidth() / 2 + Epsilon);
            }

            // If we collide, we cancel any velocity
            // in the X direction
            newV.SetX(0);
        }
    }

    // Update the velocity and position
    mV = newV;
    SetLocation(newP.X(), newP.Y());

    if (mP.Y() > GetGame()->GetHeight() && mCollideable == true)
    {
        GetGame()->GameOver();
    }

    auto collisions = GetGame()->GetInteracts();
    for (auto item : collisions)
    {
        if (mCollideable)
            item->Collision();
    }

    UpdateImage();   
}

/** Sets the gnomes y velocity
* \param y the gnomes new y velocity
* \returns None
*/
void CItemGnome::SetYVelocity(double y)
{
    // If player is not in the air
    if (mV.Y() == 0)
    {
        mV.SetY(mV.Y() + y);
    }
}

/// Find player object
/// \returns true if object is player
bool CItemGnome::IsPlayer()
{
    return true;
}

void CItemGnome::UpdateImage()
{
    if (mV.X() == 0)
        CItem::SetImage(ItemGnomeImage);

    else if (mV.X() < 0)
    {
        if (GnomeImage != ItemWalkLeftImage1)
        {
            CItem::SetImage(ItemWalkLeftImage1);
            GnomeImage = ItemWalkLeftImage1;
        }
        else
        {
            if (mV.Y() == 0)
            {
                CItem::SetImage(ItemWalkLeftImage2);
                GnomeImage = ItemWalkLeftImage2;
            }
            else
            {
                CItem::SetImage(ItemWalkLeftImage1);
                GnomeImage = ItemWalkLeftImage1;
            }
        }
    }
    else if (mV.X() > 0)
    {
        if (GnomeImage != ItemWalkRightImage1)
        {
            CItem::SetImage(ItemWalkRightImage1);
            GnomeImage = ItemWalkRightImage1;
        }
        else
        {
            if (mV.Y() == 0)
            {
                CItem::SetImage(ItemWalkRightImage2);
                GnomeImage = ItemWalkRightImage2;
            }
            else
            {
                CItem::SetImage(ItemWalkRightImage1);
                GnomeImage = ItemWalkRightImage1;
            }
        }
    }
}

void CItemGnome::Reset(double x, double y)
{
    mV.SetX(0);
    mV.SetY(10);
    mP.SetX(x);
    mP.SetY(y);
    mCollideable = true;
}
