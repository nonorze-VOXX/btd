#pragma once
#include <unordered_map>

#include "DB.h"
#include "BtdTimer.h"
#include "map.h"
#include "Tower.h"
#define SCREEN_SIZE_X 1000
#define SCREEN_SIZE_Y 770
namespace Btd
{
    class GameManager
    {
    private:
        bool IsLose = false;
        bool IsWin = true;
        int live = 10;
        int money = 0;
        bool BloonPause = false;
        int willDecreaseMoney = 0;
        unordered_map<UINT,Layer> shortKeyMap;

    public:
        void OnBeginState(); // 設定每次重玩所需的變數
        void OnInit(); // 遊戲的初值及圖形設定
        void OnKeyDown(UINT, UINT, UINT);
        void OnKeyUp(UINT, UINT, UINT);
        void OnLButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
        void OnLButtonUp(UINT nFlags, CPoint point); // 處理滑鼠的動作
        void OnMouseMove(UINT nFlags, CPoint point); // 處理滑鼠的動作 
        void OnRButtonDown(UINT nFlags, CPoint point); // 處理滑鼠的動作
        void OnRButtonUp(UINT nFlags, CPoint point); // 處理滑鼠的動作
        void OnMove(); // 移動遊戲元素
        void OnShow(); // 顯示這個狀態的遊戲畫面
        int GetLive() const { return live; }
        int GetMoney() const { return money; }
        int GetRound() const { return round; }

        bool GetLose();
        bool GetWin();
        bool GetGoToInit()
        {
            if(GetLose())
            {
                gameOverCounter++;
                if(gameOverCounter>=170)
                {
                    return true;
                }
            }
            if(GetWin())
            {
                return true;
            }
            return false;
        }

        vector<GameText> GetGameText()
        {
            vector<GameText> texts;
            texts.push_back({"Round:   "+to_string(GetRound()+1),{749,25},RGB(255,255,255),27});
            texts.push_back({"Money: "+to_string(GetMoney()),{749,61},RGB(255,255,255),27});
            texts.push_back({"Lives:  "+to_string(GetLive()),{749,97},RGB(255,255,255),27});

            texts.push_back({"Build Towers",{749,152},RGB(255,255,255),24});
            texts.push_back({"____________",{749,152},RGB(255,255,255),24});

            if(GetLose())
            {
                Vector2 screenCenter = {(float)SCREEN_SIZE_X/2,(float)SCREEN_SIZE_Y/2};
                Vector2 TextPosition = Vector2Sub(screenCenter,{ (float)(2.5 *gameOverCounter), (float)gameOverCounter });
                float offset = (float)gameOverCounter /30.f;
                texts.push_back({"game over", Vector2Add(TextPosition,{offset,0}),RGB(255,255,255),gameOverCounter});
                texts.push_back({"game over", Vector2Add(TextPosition,{0,offset}),RGB(255,255,255),gameOverCounter});
                texts.push_back({"game over", Vector2Add(TextPosition,{-offset,0}),RGB(255,255,255),gameOverCounter});
                texts.push_back({"game over", Vector2Add(TextPosition,{0,-offset}),RGB(255,255,255),gameOverCounter});
                texts.push_back({"game over", TextPosition,RGB(0,0,0),gameOverCounter});
            }
            return texts;
        }
        int gameOverCounter =0;
        static shared_ptr<Map> map;
        GameFlow GameFlow;
        BtdTimer BtdTimer;
        int round = 0;
        GameObject startButton;
        DB db;
    };
}
