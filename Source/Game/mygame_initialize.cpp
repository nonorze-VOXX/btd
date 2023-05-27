#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "BtdClass/GameObject.h"
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "BtdClass/BtdUtil.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g) : CGameState(g)
{
}

void CGameStateInit::InitSelectedMaps()
{
    vector<string> backgroundBmps[3] = {
        {"resources/map/easy/map.bmp"},
        {"resources/map/medium/map.bmp"},
        {"resources/map/hard/map.bmp"}
    };
    for (int i = 0; i < 3; i++)
    {
        auto m = make_shared<Btd::Map>(Btd::Map());
        m->InitBackground(static_cast<Btd::MapType::MapType>(i));
        m->InitRoad(static_cast<Btd::MapType::MapType>(i));
        m->SetMapType(static_cast<Btd::MapType::MapType>(i));
        selectedMaps.push_back(m);
    }
}

void CGameStateInit::OnInit()
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(0, "Ninja kiwi!"); // 一開始的loading進度為0%
    //
    // 開始載入資料
    //
    //Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
    //
    // 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
    //
    vector<pair<int, int>> medalLoc = {
        {210, 325}, {390, 325}, {570, 325}
    };
    for (int i=0; i<3; i++)
    {
        _mapButton[i].SetCenter(medalLoc[i].first, medalLoc[i].second);
    }
    InitSelectedMaps();
    map = make_shared<Btd::Map>(Btd::Map());
    map = selectedMaps[0];
}

void CGameStateInit::OnBeginState()
{
    LoadPassedMap();
    vector<vector<string>> medalPath = {
        {"resources/medal/easy.bmp", "resources/medal/easy_medal.bmp", "resources/medal/play.bmp"},
        {"resources/medal/medium.bmp", "resources/medal/medium_medal.bmp", "resources/medal/play.bmp"},
        {"resources/medal/hard.bmp", "resources/medal/hard_medal.bmp", "resources/medal/play.bmp"}
    };
    for (int i=0; i<3; i++)
    {
        _mapButton[i].LoadBitmapByString(medalPath[i]);
        _mapButton[i].SetFrameIndexOfBitmap(passedMap[i]);
    }
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}


void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    for (int i = 0; i < 3; i++)
    {
        if (IsCursorInObj(static_cast<Btd::GameObject>(_mapButton[i])))
        {
            _mapButton[i].SetClicked(true);
            map->SetRoutesByMap(static_cast<Btd::MapType::MapType>(i));
            Btd::GameManager::map = map;
            GotoGameState(GAME_STATE_RUN);
        }
    }
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
    if (_mapButton[2].IsBitmapLoaded())
    {
        for (int i = 0; i < 3; i++)
        {
            if (IsCursorInObj(static_cast<Btd::GameObject>(_mapButton[i])))
            {
                map = selectedMaps[i];
            }
        }
    }
}

void showInfoText(Btd::Map map)
{
    CDC* pDC = CDDraw::GetBackCDC();
    CTextDraw::ChangeFontLog(pDC, 27, "Courier New", RGB(255, 255, 255), 620);
    CTextDraw::Print(pDC, 749, 25, "Round:   1");
    CTextDraw::Print(pDC, 749, 61, "Money: " + to_string(map.GetInitMoney()));
    CTextDraw::Print(pDC, 749, 97, "Lives:  " + to_string(map.GetInitLives()));

    CTextDraw::ChangeFontLog(pDC, 24, "Courier New", RGB(255, 255, 255), 620);
    CTextDraw::Print(pDC, 749, 152, "Build Towers");
    CTextDraw::Print(pDC, 749, 152, "____________");

    CDDraw::ReleaseBackCDC();
}

void CGameStateInit::LoadPassedMap()
{
    std::string delimiter = ",";
    std::ifstream fin("resources/medal/passedMap.csv");
    while (fin)
    {
        std::string s;
        getline(fin, s);
        size_t pos = 0;
        std::string tmp;
        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            tmp = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            passedMap[0] = stoi(tmp);
            
            pos = s.find(delimiter);
            tmp = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            passedMap[1] = stoi(tmp);
            
            pos = s.find(delimiter);
            tmp = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            passedMap[2] = stoi(tmp);
        }
        fin.close();
    }
}

void CGameStateInit::OnShow()
{
    map->ShowBackground();
    map->ShowRoad();
    for (int i = 0; i < 3; i++)
    {
        _mapButton[i].ShowBitmap();
    }
    showInfoText(*map);
}
