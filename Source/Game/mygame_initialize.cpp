#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "BtdClass/GameObject.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Ninja kiwi!");	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	//Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
	background.LoadBitmapByString({ "resources/map.bmp" });
	background.SetTopLeft(0, 0);
	startButton.LoadBitmapByString({ "resources/start_button.bmp" });
	startButton.SetTopLeft(742, 620);
	initRoad();
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

bool isPointInBmp(POINT p, CMovingBitmap target) 
{
	if (target.GetLeft() <= p.x && p.x <= target.GetLeft() + target.GetWidth() &&
		target.GetTop() <= p.y && p.y <= target.GetTop() + target.GetHeight()) {
		return true;
	}
	return false;
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	POINT p;
	GetCursorPos(&p);
	HWND hwnd = FindWindowA(NULL, "Game");
	ScreenToClient(hwnd, &p);

	if (isPointInBmp(p, startButton)) {
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}
}

void showInfoText() {
	CDC *pDC = CDDraw::GetBackCDC();
	CTextDraw::ChangeFontLog(pDC, 27, "Courier New", RGB(255, 255, 255), 620);
	CTextDraw::Print(pDC, 749, 25, "Round:   1");
	CTextDraw::Print(pDC, 749, 61, "Money: 650");
	CTextDraw::Print(pDC, 749, 97, "Lives:  40");

	CTextDraw::ChangeFontLog(pDC, 24, "Courier New", RGB(255, 255, 255), 620);
	CTextDraw::Print(pDC, 749, 152, "Build Towers");
	CTextDraw::Print(pDC, 749, 152, "____________");

	CDDraw::ReleaseBackCDC();
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
	startButton.ShowBitmap();
	showInfoText();
	for (int i = 0; i < 15; i++) {
		road[i].ShowBitmap();
	}
}

void CGameStateInit::initRoad()
{
	char buff[100];
	string roadFileName;
	for (int i = 0; i < 15; i++) {
		Btd::GameObject tmpRoad;
		sprintf(buff, "resources/road_%d.bmp", i+1);
		tmpRoad.LoadBitmapByString({ buff });
		road.push_back(tmpRoad);
	}
	road[0].SetTopLeft(0, 320);
	road[1].SetTopLeft(105, 124);
	road[2].SetTopLeft(170, 124);
	road[3].SetTopLeft(285, 190);
	road[4].SetTopLeft(285, 390);
	road[5].SetTopLeft(43, 510);
	road[6].SetTopLeft(43, 575);
	road[7].SetTopLeft(110, 636);
	road[8].SetTopLeft(620, 426);
	road[9].SetTopLeft(429, 428);
	road[10].SetTopLeft(429, 249);
	road[11].SetTopLeft(496, 249);
	road[12].SetTopLeft(622, 46);
	road[13].SetTopLeft(368, 48);
	road[14].SetTopLeft(368, 0);
}
