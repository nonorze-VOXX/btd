#pragma once
#include "Tower.h"

namespace Btd
{
    class Cannon : public Tower
    {
    public:
        Cannon();
        void Shoot(Vector2 target) override;
        void PushThrowablePool();
        void Upgrade(int level) override;
    };
}

