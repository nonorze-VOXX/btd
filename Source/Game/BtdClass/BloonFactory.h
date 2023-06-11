#pragma once
#include <queue>

#include "Bloon.h"
#include "Map.h"
#include "TowerFactory.h"

namespace Btd
{
    class BloonFactory
    {
    public:
        static queue<Bloon> BloonPool;
        static vector<Bloon> BloonVector;
        static vector<UnitRound> BloonRound;
        static int BloonCounter;
        static int BloonTimer;
        static int BloonId;
        static vector<string> balloonPath;
        static int RoundRoute;

        static void SetNextRound(vector<UnitRound> rounds);

        static bool UpdateRound(int DeltaTime);

        static void MakeBloon(Layer type);

        static void MakeBloonByPosition(Layer type,
                                        Vector2 startPosition, int nowRouteTarget, int route);

        static void UpdateBloon(int *increaseMoney);

        static void handlePopBalloon(int *increaseMoney);

        static void ClearActiveBloon();

        static int subLifeByGoalBloon();
    };
} // namespace Btd
