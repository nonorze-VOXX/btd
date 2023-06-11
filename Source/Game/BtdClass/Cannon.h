#pragma once
#include "Tower.h"

namespace Btd
{
    class Cannon : public Tower
    {
    public:
        Cannon()
        {
            _range = 200;
            shootDeltaTime = 6;
            ThrowablePath = {"resources/towers/bomb/bomb.bmp", "resources/towers/bomb/bomb_1.bmp",
            "resources/towers/bomb/bomb_2.bmp", "resources/towers/bomb/bomb_3.bmp", "resources/towers/bomb/bomb_4.bmp"};
            UpgradePrice[0] = 380;
            UpgradePrice[1] = 180;
            SetDamageType(DamageType::Boom);
        }
        void Shoot(Vector2 target) override;
        void PushThrowablePool();
        void Upgrade(int level) override;
    };
}

