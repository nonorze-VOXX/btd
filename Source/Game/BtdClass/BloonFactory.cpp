#include "stdafx.h"
#include "BloonFactory.h"

namespace Btd
{
    queue<Bloon> BloonFactory::BloonPool = queue<Bloon>();
    vector<Bloon> BloonFactory::BloonVector = vector<Bloon>();
    vector<UnitRound> BloonFactory::BloonRound;
    int BloonFactory::BloonCounter = 0;
    int BloonFactory::BloonTimer = 0;
    int BloonFactory::RoundRoute = 0;
    int BloonFactory::BloonId = 0;
    vector<string> BloonFactory::balloonPath = {
        "Resources/bloon/bloon_red.bmp", "Resources/bloon/bloon_blue.bmp", "Resources/bloon/bloon_green.bmp",
        "Resources/bloon/bloon_yellow.bmp", "Resources/bloon/bloon_black.bmp",
        "Resources/bloon/bloon_white.bmp","Resources/bloon/bloon_rainbow.bmp","Resources/bloon/bloon_lead.bmp", "Resources/bloon/explode.bmp"
    };

    void BloonFactory::SetNextRound(vector<UnitRound> rounds)
    {
        BloonRound = rounds;
        BloonCounter = 0;
        BloonTimer = 0;
    }

    bool BloonFactory::UpdateRound(int DeltaTime)
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

    void BloonFactory::MakeBloon(Layer type)
    {
        Vector2 position = Map::GetRoute()[RoundRoute][0];
        MakeBloonByPosition(type, position, 0, RoundRoute);
        RoundRoute += 1;
        RoundRoute %= Map::GetRoute().size();
    }

    void BloonFactory::MakeBloonByPosition(Layer type, Vector2 startPosition, int nowRouteTarget, int route)
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

    void BloonFactory::UpdateBloon(int* increaseMoney)
    {
        for (Bloon& b : BloonVector)
        {
            b.Update();
        }
        handlePopBalloon(increaseMoney);
    }

    void BloonFactory::handlePopBalloon(int* increaseMoney)
    {
        for (int i = 0; i < static_cast<int>(BloonVector.size()); i++)
        {
            Bloon b = BloonVector[i];
            if (BloonVector[i].IsPoped())
            {
                (*increaseMoney) += 1;
                BloonType::BloonType type = BloonVector[i].GetType();
                Vector2 offset = {15,15};
                if (type == BloonType::black || type == BloonType::white)
                {
                    int nowRouteTarget = BloonVector[i].GetNowRouteTarget();
                    Vector2 position = b.GetBottomCenter();
                    MakeBloonByPosition(Layer::yellow, Vector2Add(position,offset), nowRouteTarget, b.Getroute());
                    MakeBloonByPosition(Layer::yellow, position, nowRouteTarget, b.Getroute());
                }else if (type == BloonType::rainbow || type == BloonType::lead)
                {
                    int nowRouteTarget = BloonVector[i].GetNowRouteTarget();
                    Vector2 position = b.GetBottomCenter();
                    MakeBloonByPosition(Layer::black, Vector2Add(position,offset), nowRouteTarget, b.Getroute());
                    MakeBloonByPosition(Layer::white, position, nowRouteTarget, b.Getroute());
                }
                BloonPool.push(BloonVector[i]);
                BloonVector.erase(BloonVector.begin() + i);
            }
        }
    }

    void BloonFactory::ClearActiveBloon()
    {
        for (auto& b : BloonVector)
        {
            BloonPool.push(b);
        }
        BloonVector.clear();
    }

    int BloonFactory::subLifeByGoalBloon()
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
}
