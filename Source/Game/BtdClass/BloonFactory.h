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

        static void SetNextRound(vector<UnitRound> rounds)
        {
            BloonRound = rounds;
            BloonCounter = 0;
            BloonTimer = 0;
        }

        static bool UpdateRound(int DeltaTime)
        {
            if (BloonTimer <= 0)
            {
                if (BloonCounter >= static_cast<int>(BloonRound.size()))
                {
                    return true;
                }
                MakeBloon(BloonRound[BloonCounter].type);
                BloonTimer = BloonRound[BloonCounter].nextTime;
                BloonCounter++;
            }
            else
            {
                BloonTimer -= DeltaTime;
            }
            return false;
        }

        static void MakeBloon(Layer type)
        {
            Vector2 position = Map::GetRoute()[RoundRoute][0];
            MakeBloonByPosition(type, position, 0, RoundRoute);
            RoundRoute += 1;
            RoundRoute %= Map::GetRoute().size();
        }

        static void MakeBloonByPosition(Layer type,
                                        Vector2 startPosition, int nowRouteTarget, int route)
        {
            if (BloonPool.empty())
            {
                Bloon tmpBloon;
                tmpBloon.LoadBitmapByString(balloonPath, RGB(0, 0, 0));
                tmpBloon.SetLayer(0);
                tmpBloon.SetFrameIndexOfBitmap(0);
                tmpBloon.SetBottomCenter(static_cast<int>(startPosition.X),
                                         static_cast<int>(startPosition.Y));
                tmpBloon.SetActive(false);
                BloonPool.push(tmpBloon);
            }
            auto next = BloonPool.front();
            next.Init();
            switch (type)
            {
            case Layer::black:
                next.SetFrameIndexOfBitmap((int)Layer::black);
                next.SetLayer(0);
                next.Setspeed(3);
                next.SetType(BloonType::black);
                break;
            case Layer::white:
                next.SetFrameIndexOfBitmap((int)Layer::white);
                next.SetLayer(0);
                next.Setspeed(3);
                next.SetType(BloonType::white);
                break;
            case Layer::rainbow:
                next.SetFrameIndexOfBitmap((int)Layer::rainbow);
                next.SetLayer(0);
                next.Setspeed(3);
                next.SetType(BloonType::rainbow);
                break;
            case Layer::lead:
                next.SetFrameIndexOfBitmap((int)Layer::lead);
                next.SetLayer(0);
                next.Setspeed(3);
                next.SetType(BloonType::lead);
                break;
            default:
                next.LoadBitmapByString(balloonPath, RGB(0, 0, 0));
                next.SetLayer((int)type);
                next.SetFrameIndexOfBitmap((int)type);
                next.Setspeed(3);
                next.Setspeed(
                    static_cast<float>(0.5 * static_cast<float>(next.GetLayer()) * static_cast<float>(next.GetLayer()) +
                        static_cast<float>(next.GetLayer()) +
                        3));
                next.SetType(BloonType::normal);
                break;
            }
            next.SetNowRouteTarget(nowRouteTarget);
            next.SetBottomCenter(static_cast<int>(startPosition.X),
                                 static_cast<int>(startPosition.Y));
            next.SetActive(true);
            next.SetIsPoped(false);
            next.SetIsGoaled(false);
            next.SetRoute(route);
            next.SetId((BloonId++)%999999);  // every bloon has an id, every 999999 a loop
            BloonPool.pop();
            BloonVector.push_back(next);
        }

        static void UpdateBloon(int *increaseMoney)
        {
            for (Bloon& b : BloonVector)
            {
                b.Update();
            }
            handlePopBalloon(increaseMoney);
        }

        static void handlePopBalloon(int *increaseMoney)
        {
            for (int i = 0; i < static_cast<int>(BloonVector.size()); i++)
            {
                Bloon b = BloonVector[i];
                if (BloonVector[i].IsPoped())
                {
                    (*increaseMoney) += 1;
                    BloonType::BloonType type = BloonVector[i].GetType();
                    if (type == BloonType::black || type == BloonType::white)
                    {
                        int nowRouteTarget = BloonVector[i].GetNowRouteTarget();
                        Vector2 position = b.GetBottomCenter();
                        MakeBloonByPosition(Layer::yellow, position, nowRouteTarget, b.Getroute());
                        MakeBloonByPosition(Layer::yellow, position, nowRouteTarget, b.Getroute());
                    }else if (type == BloonType::rainbow || type == BloonType::lead)
                    {
                        int nowRouteTarget = BloonVector[i].GetNowRouteTarget();
                        Vector2 position = b.GetBottomCenter();
                        MakeBloonByPosition(Layer::black, position, nowRouteTarget, b.Getroute());
                        MakeBloonByPosition(Layer::white, position, nowRouteTarget, b.Getroute());
                    }
                    BloonPool.push(BloonVector[i]);
                    BloonVector.erase(BloonVector.begin() + i);
                }
            }
        }

        static void ClearActiveBloon()
        {
            for (auto& b : BloonVector)
            {
                BloonPool.push(b);
            }
            BloonVector.clear();
        }

        static int subLifeByGoalBloon()
        {
            int subLife = 0;
            for (int i = 0; i < static_cast<int>(BloonVector.size()); i++)
            {
                Bloon b = BloonVector[i];
                if (b.IsGoaled())
                {
                    BloonType::BloonType type = b.GetType();
                    if (type == BloonType::black || type == BloonType::white)
                    {
                        subLife += 5;
                    }
                    else
                    {
                        subLife += b.GetLayer() + 1;
                    }
                    BloonPool.push(BloonVector[i]);
                    BloonVector.erase(BloonVector.begin() + i);
                }
            }
            return subLife;
        }
    };
} // namespace Btd
