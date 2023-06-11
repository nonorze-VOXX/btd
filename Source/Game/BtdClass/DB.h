#pragma once
#include <fstream>
#include <iostream>
#include <string>

#include "BtdUtil.h"

namespace Btd
{
    class DB
    {
    private:
        vector<vector<UnitRound>> _roundses;

    public:
        void LoadRounds();
        vector<vector<UnitRound>> GetRounds();
        void LoadPassedMap (int passedMap[3]);
        void PassMap (MapType type);
    };
} // namespace Btd
