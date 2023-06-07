#pragma once
#include "Tower.h"

namespace Btd
{
    
    class Super:public Tower
    {
    public:
        Super()
        {
            _range = 100;
            shootDeltaTime = 0.3f;
            ThrowablePath = {
            "resources/towers/monkey/dart_1.bmp", "resources/towers/monkey/dart_2.bmp",
            "resources/towers/monkey/dart_3.bmp", "resources/towers/monkey/dart_4.bmp",
            "resources/towers/monkey/dart_5.bmp", "resources/towers/monkey/dart_6.bmp",
            "resources/towers/monkey/dart_7.bmp", "resources/towers/monkey/dart_8.bmp"
            };
            UpgradePrice[0] = 320;
            UpgradePrice[1] = 200;
            SetDamageType(DamageType::Normal);
        }
        void Shoot(Vector2 target) override;
        void PushThrowablePool() override;
		void Upgrade(int level) override;
    
    };
}
