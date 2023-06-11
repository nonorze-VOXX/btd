#pragma once
#include "Boomerang.h"
#include "Tower.h"

namespace Btd
{
    class BoomerangMonkey : public Tower
    {
    public:
        BoomerangMonkey();

        void UpdateThrowable() override;


        void Shoot(Vector2 target) override;
        void PushThrowablePool() override;
		void Upgrade(int level) override;
        
    };
}
