#pragma once
#include <unordered_map>

#include "DB.h"
#include "BtdTimer.h"
#include "map.h"
#include "Tower.h"
#include "Cavallo.h"

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
        bool GetGoToInit();

        vector<GameText> GetGameText();
        int gameOverCounter =0;
        static shared_ptr<Map> map;
        GameFlow GameFlow;
        BtdTimer BtdTimer;
        int round = 0;
        GameObject startButton;
        DB db;
        Cavallo 🐼;
    };
}
