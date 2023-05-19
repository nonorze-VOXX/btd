#ifndef MAP_H
#define MAP_H

#include "GameObject.h"
#include "BtdUtil.h"
#include "FactoryButton.h"
#include "SoundButton.h"

namespace Btd
{
    class Map : public GameObject
    {
    public:
        Map() = default;
        ~Map() override = default;
        void SetRoutesByMap(MapType::MapType type);
        int HandleShortCut(UINT uint, int money);
        const int InitMoney = 650;
        const int InitLives = 40;
        virtual void InitRoad(MapType::MapType type);
        void ShowRoad();
        virtual void InitBackground(MapType::MapType type);
        void ShowBackground();
        void InitFactoryButton();
        void ShowFactoryButton();
        void UpdateFactoryButton();
        int HandleButtonClicked(int money);
        GameObject GetBackground();
        vector<vector<UnitRound>> GetRounds();
        void SetRounds(vector<vector<UnitRound>> round);
        static vector<vector<Vector2>> GetRoute();
        static void SetRoute(vector<vector<Vector2>>);
        bool IsOverLapRoad(GameObject target);
        bool IsOverSidebar(GameObject target);
        int GetInitMoney();
        int GetInitLives();

    protected:
        std::vector<GameObject> _road;
        GameObject _background;
        vector<FactoryButton> _factoryButton;
        static vector<vector<Vector2>> _route;
        vector<vector<UnitRound>> _rounds;
        GameObject _sidebar;
        int buttonNumber=0;
        vector<int> priceTable ;
        SoundButton soundButton;
    };
}

#endif
