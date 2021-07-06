/**
 * \file Background.cpp
 *
 * \author Paul Schulte
 */

#include "pch.h"
#include "Background.h"
#include <string>

using namespace Gdiplus;
using namespace std;

/// Background filename 
const wstring BackgroundImageName = L"images/backgroundColorGrass.png";

/** Constructor
 * \param game The game this is a member of
 * \param image The image used for the background
*/
CBackground::CBackground(CGame* game, const std::wstring image) : CItem(game, image)
{

}

