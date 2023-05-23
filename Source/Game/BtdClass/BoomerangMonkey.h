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
            _range = 100;
            ThrowablePath = {
                "resources/towers/boomerang/Boomerang_1.bmp", "resources/towers/boomerang/Boomerang_2.bmp",
                "resources/towers/boomerang/Boomerang_3.bmp", "resources/towers/boomerang/Boomerang_4.bmp",
                "resources/towers/boomerang/Boomerang_5.bmp", "resources/towers/boomerang/Boomerang_6.bmp",
                "resources/towers/boomerang/Boomerang_7.bmp", "resources/towers/boomerang/Boomerang_8.bmp"
            };
            SetDamageType(DamageType::Normal);
        }

        void UpdateThrowable() override;


        void Shoot(Vector2 target) override;
        void PushThrowablePool() override;
		void Upgrade(int level) override;
        
    };
}
