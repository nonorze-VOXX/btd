#pragma once
#include "Tower.h"

namespace Btd
{
    class NailMachine : public Tower
    {
    public:
        NailMachine();
        void Update() override;
        void PushThrowablePool();
        void Upgrade(int level) override;
    };
}
