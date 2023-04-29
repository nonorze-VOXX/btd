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
        iceGas->SetPenetrate(true);
        iceGas->SetRealCenter(GetCenter());
        iceGas->SetRange(_range);
        iceGas->SetFreezeTime(_freezeTime);
        throwablePool.push(iceGas);
    }

    void IceTower::TowerShow()
    {
        if (_isClicked)
        {
            this->RangeCircle.ShowBitmap((float)_range / 100.0);
            if (!_isMovable)
            {
                this->UpgradeBtn[0].ShowBitmap();
                this->UpgradeBtn[1].ShowBitmap();
            }
        }
        for (int i=0; i<(int)throwables.size(); i++)
        {
            throwables[i]->SetCenter((int)GetCenter().X - (_range - 75),
                (int)GetCenter().Y - (_range - 75));
            throwables[i]->ShowBitmap(_range / 75.0);
        }
        this->ShowBitmap();
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
