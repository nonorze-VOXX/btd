#include "stdafx.h"
#include "IceTower.h"

#include "IceGas.h"

namespace Btd
{
    IceTower::IceTower()
    {
        _range = 80;
        shootDeltaTime = 9;
        ThrowablePath = {"resources/towers/ice/ice.bmp"};
        _freezeTime = 450;
        UpgradePrice[0] = 270;
        UpgradePrice[1] = 180;
    }

    void IceTower::PushThrowablePool()
    {
        shared_ptr<IceGas> iceGas = make_shared<IceGas>(IceGas());
        iceGas->LoadBitmapByString(ThrowablePath, RGB(0, 0, 0));
        iceGas->SetSpeed(0);
        iceGas->SetMaxExistTime(70);
        iceGas->SetMaxExistTime(150);
        iceGas->SetRealCenter(GetCenter());
        iceGas->SetRange(_range);
        iceGas->SetFreezeTime(_freezeTime);
        throwablePool.push(iceGas);
    }

    void IceTower::TowerShow()
    {
        for (int i=0; i<(int)throwables.size(); i++)
        {
            Vector2 tmp = throwables[i]->GetCenter();
            throwables[i]->SetCenter((int)GetCenter().X - (_range - 75),
                (int)GetCenter().Y - (_range - 75));
            throwables[i]->ShowBitmap(_range / 75.0);
            throwables[i]->SetCenter((int)tmp.X,(int)tmp.Y);
        }
        Tower::TowerShow();
    }

    void IceTower::Upgrade(int level)
    {
        Tower::Upgrade(level);
        switch (level)
        {
        case 0:
            _freezeTime = 600;
            break;
        case 1:
            _range = 120;
            break;
        default:
            break;
        }
        IsUpgrade[level] = true;
    }
}
