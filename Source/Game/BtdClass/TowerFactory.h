#pragma once

#include "Cannon.h"
#include "DartMonkey.h"
#include "Glue.h"
#include "IceTower.h"
#include "NailMachine.h"
#include "Spikes.h"

namespace Btd
{
    class TowerFactory
    {
    public:
        TowerFactory() { }
        ~TowerFactory() {}
        static vector<shared_ptr<Tower>> TowerVector;
        static vector<shared_ptr<Placeable>> PlaceableVector;
        static void MakeTower (TowerType attribute);
        static int HandleTowerClicked(int money);
        static void UpdateSpikesVector();
        static void SetPriceTable(vector<int> priceTable);

    private: 
        static vector<int> PriceTable;
    };
}
