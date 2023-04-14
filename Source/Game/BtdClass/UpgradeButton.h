#pragma once
#include "Button.h"

namespace Btd
{
    class UpgradeButton: public Button
    {
    public:
        UpgradeButton();
        ~UpgradeButton() = default;
        void Init();
        void Update() override;
    };
}
