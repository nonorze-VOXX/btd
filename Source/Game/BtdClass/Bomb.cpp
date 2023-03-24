﻿#include "stdafx.h"
#include "Bomb.h"

#include "BallonFactory.h"

namespace Btd
{
    Bomb::Bomb()
    {
        SetAnimation(50, true);
    }

    void Bomb::DetectHitBalloon()
    {
        for (int i=0; i<(int)BallonFactory::BallonVector.size(); i++)
        {
            bool isHited = false;
            for (int j=0; j<(int)cantHitBloons.size(); j++)
            {
                if (cantHitBloons[j].first == &BallonFactory::BallonVector[i])
                {
                    isHited = true;
                    break;
                }
            }
            if (Btd::IsOverlap(*this, BallonFactory::BallonVector[i])&&
                !isHited )//not in cant hit bloon)
            {
                if (GetFrameIndexOfBitmap() == 0)
                {
                    ToggleAnimation();
                    _existTime =0;
                    _maxExistTime = 75;
                }
                else
                {
                    BallonFactory::BallonVector[i].Pop(1, Normal);
                    cantHitBloons.push_back({&BallonFactory::BallonVector[i], 0});
                }
                _speed = 0;
            }
        }
    }
}
