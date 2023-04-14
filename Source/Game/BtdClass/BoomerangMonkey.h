#pragma once
#include "Boomerang.h"
#include "Tower.h"

namespace Btd
{
    class BoomerangMonkey : public Tower
    {
    public:
        BoomerangMonkey()
        {
            _range = 300;
            ThrowablePath = {
                "resources/towers/bomb/bomb.bmp", "resources/towers/bomb/bomb_1.bmp",
                "resources/towers/bomb/bomb_2.bmp", "resources/towers/bomb/bomb_3.bmp"
            };
        }

        void UpdateThrowable() override;


        void Shoot(Vector2 target) override;
        void PushThrowablePool() override;
    };
}
