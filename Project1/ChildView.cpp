
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "ItemGnome.h"
#include "Level.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Gdiplus;


// CChildView
/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Maximum amount of time to allow for elapsed
const double MaxElapsed = 0.050;

 /**
  * Constructor
  */
CChildView::CChildView()
{
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
	ON_COMMAND(ID_LEVEL_LEVEL1, &CChildView::OnLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
    ON_WM_TIMER()
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
* This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
* \returns None
*/
void CChildView::OnPaint() 
{
    CPaintDC paintDC(this);
    CDoubleBufferDC dc(&paintDC); // device context for painting
    Graphics graphics(dc.m_hDC);

    CRect rect;
    GetClientRect(&rect);

    mGame.setGraphics(&graphics);
    mGame.OnDraw(rect.Width(), rect.Height());

    if (mFirstDraw)
    {
        mFirstDraw = false;
        SetTimer(1, FrameDuration, nullptr);

        /*
         * Initialize the elapsed time system
         */
        LARGE_INTEGER time, freq;
        QueryPerformanceCounter(&time);
        QueryPerformanceFrequency(&freq);

        mLastTime = time.QuadPart;
        mTimeFreq = double(freq.QuadPart);
    }

    /*
    * Compute the elapsed time since the last draw
    */
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    long long diff = time.QuadPart - mLastTime;
    double elapsed = double(diff) / mTimeFreq;
    mLastTime = time.QuadPart;

    //
    // Prevent tunnelling
    //
    while (elapsed > MaxElapsed)
    {
        mGame.Update(MaxElapsed);

        elapsed -= MaxElapsed;
    }

    // Consume any remaining time
    if (elapsed > 0)
    {
        mGame.Update(elapsed);
    }
}

/**
* loads level 0.
*
* \returns None
*/
void CChildView::OnLevelLevel0()
{
    mGame.Load(0);
}

/**
* loads level 1.
*
* \returns None
*/
void CChildView::OnLevelLevel1()
{
    mGame.Load(1);
}

/**
* loads level 2.
*
* \returns None
*/
void CChildView::OnLevelLevel2()
{
    mGame.Load(2);
}

/**
* loads level 3.
*
* \returns None
*/
void CChildView::OnLevelLevel3()
{
    mGame.Load(3);
}


/**
* stops the gnome from moving when left or right buttons are no longer being pressed.
*
* \param nChar
* \param nRepCnt
* \param nFlags
* \returns None
*/
void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    shared_ptr<CItemGnome> gnome = mGame.GetGnome();

	switch (nChar)
	{
	    case VK_RIGHT:
            gnome->Stop();
	    case VK_LEFT:
            gnome->Stop();
	}
}

/**
* moves the gnome left, right or up depending on what button was pressed.
*
* \param nChar
* \param nRepCnt
* \param nFlags
* \returns None
*/
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    shared_ptr<CItemGnome> gnome = mGame.GetGnome();

	switch (nChar)
	{
	case VK_RIGHT:
        gnome->UpdateRight();
        break;

	case VK_LEFT:
        gnome->UpdateLeft();
        break;

	case VK_SPACE:
        gnome->UpdateJump();
        break;
	}
}

/**
 * Handle timer events
 * \param nIDEvent The timer event ID
 * \returns None
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    Invalidate();
    CWnd::OnTimer(nIDEvent);
}

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    return false;
}
