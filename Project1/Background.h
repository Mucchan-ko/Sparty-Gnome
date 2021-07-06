/**
 * \file Background.h
 *
 * \author Paul Schulte
 *
 * Class to implement Background structure
 */

#pragma once
#include "Item.h"
#include <string>

/**
 * Implements a background item
 */
class CBackground : public CItem
{
public:
    CBackground::CBackground(CGame* game, const std::wstring image);

    /// Default constructor (disabled)
    CBackground() = delete;

    /// Copy constructor (disabled)
    CBackground(const CBackground&) = delete;
};

