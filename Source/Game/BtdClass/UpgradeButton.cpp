#include "stdafx.h"
#include "UpgradeButton.h"

namespace Btd
{
    UpgradeButton::UpgradeButton()
    {
    }

    void UpgradeButton::Init()
    {
        LoadBitmapByString({"resources/button/cantBuy.bmp", "resources/button/notBuy.bmp"
        , "resources/button/alreadyBought.bmp"});
    }

    void UpgradeButton::Update()
    {
        if (_isClicked)
        {
            
        }
    }
}
