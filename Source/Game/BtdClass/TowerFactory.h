#pragma once

#include "Cannon.h"
#include "DartMonkey.h"
#include "IceTower.h"
#include "NailMachine.h"
#include "Spikes.h"

namespace Btd
{
    class TowerFactory
    {
    public:
        TowerFactory() {};
        ~TowerFactory() {};
        static vector<shared_ptr<Tower>> TowerVector;
        static vector<shared_ptr<Spikes>> SpikesVector;
        static void MakeTower (TowerType attribute);
        static int HandleTowerClicked(int money);
    private: 
    };
}
