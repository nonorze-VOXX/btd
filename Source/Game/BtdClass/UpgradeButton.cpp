#include "stdafx.h"
#include "UpgradeButton.h"

namespace Btd
{
    UpgradeButton::UpgradeButton()
    {
    }

    void UpgradeButton::Init()
    {
        LoadBitmapByString({"resources/button/cantBuy.bmp", "resources/button/cantBuy.bmp"
        , "resources/button/cantBuy.bmp"});
    }

    void UpgradeButton::Update()
    {
        if (_isClicked)
        {
            
        }
    }
}
