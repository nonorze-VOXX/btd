#pragma once
#include "Tower.h"

namespace Btd
{
    
    class Super:public Tower
    {
    public:
        Super();
        void Shoot(Vector2 target) override;
        void PushThrowablePool() override;
		void Upgrade(int level) override;
    
    };
}
