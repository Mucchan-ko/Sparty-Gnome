/**
 * \file ItemGnome.h
 *
 * \author Aiden Tang
 *
 * Class that implements a Gnome
 */

#pragma once
#include <memory>
#include "Item.h"
#include "Vector.h"
#include <string>

/**
 * Implements a gnome item
 */
class CItemGnome : public CItem
{
public:
    CItemGnome(CGame* game);

    /// Default constructor (disabled)
    CItemGnome() = delete;

    /// Copy constructor (disabled)
    CItemGnome(const CItem&) = delete;


    /// Setter
    /// \param x position for x direction
    /// \param y position for y direction
    void SetLocation(double x, double y);

    /// Get gnome's x position
    /// \returns x position
    double GetX() const override { return mP.X(); }

    /// Get gnome's y position
    /// \returns y position
    double GetY() const override { return mP.Y(); }

    void UpdateLeft();

    void UpdateRight();

    void UpdateJump();

    void Stop();

    void Halt();

    void Update(double elapsed);

    /// Setter for X velocity
    /// \param x velocity to add to x direction
    void SetXVelocity(double x) { mV.SetX(mV.X() + x); }

    void SetYVelocity(double y);

    /// Checks if item is player
    /// \returns true if item is gnome
    bool IsPlayer() override;

    /// Update gnomes animation image
    void UpdateImage();

    /// Reset Gnome
    /// \param x value to reset to
    /// \param y value to reset to
    /// \returns None
    void Reset(double x, double y);

    /// Make gnome invulnerable
    /// \param collide 
    /// \returns None
    void SetCollideable(bool collide) { mCollideable = collide; }

private:
    /// Gnome's Velocity Vector
    CVector mV = CVector(0, 0);

    /// Gnome's Position Vector
    CVector mP = CVector(0, 0);

    /// If gnome can interact
    bool mCollideable = true;


};

