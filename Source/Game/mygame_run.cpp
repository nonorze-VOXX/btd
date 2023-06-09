#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <string>

#include "config.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "BtdClass/TowerFactory.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
    gm.OnBeginState();
}

void CGameStateRun::OnMove() // 移動遊戲元素
{
    gm.OnMove();
    if(gm.GetGoToInit())
    {
        GotoGameState(GAME_STATE_INIT);
    }
}

void CGameStateRun::OnInit() // 遊戲的初值及圖形設定
{
    gm.OnInit();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    gm.OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    gm.OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnLButtonDown(nFlags, point);

    mouseLocal = {
        static_cast<float>(Btd::GetCursorPosX()) / static_cast<float>(SIZE_X),
        static_cast<float>(Btd::GetCursorPosY()) / static_cast<float>(SIZE_Y)
    };
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnLButtonUp(nFlags, point);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnMouseMove(nFlags, point);
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnRButtonDown(nFlags, point);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
{
    gm.OnRButtonUp(nFlags, point);
}

void CGameStateRun::OnShow()
{
    gm.OnShow();
    vector<Btd::GameText> texts = gm.GetGameText();
    CDC* pDC = CDDraw::GetBackCDC();
    for(Btd::GameText t : texts)
    {
        CTextDraw::ChangeFontLog(pDC, t.size, "Courier New", t.color,620);
        CTextDraw::Print(pDC, (int)t.position.X, (int)t.position.Y, t.text);
    }
    CDDraw::ReleaseBackCDC();
}
