#include "stdafx.h"
#include "DartMonkey.h"

namespace Btd
{
    DartMonkey::DartMonkey()
    {
        _range = 140;
        shootDeltaTime = 3;
        ThrowablePath = {
            "resources/towers/monkey/dart_1.bmp", "resources/towers/monkey/dart_2.bmp",
            "resources/towers/monkey/dart_3.bmp", "resources/towers/monkey/dart_4.bmp",
            "resources/towers/monkey/dart_5.bmp", "resources/towers/monkey/dart_6.bmp",
            "resources/towers/monkey/dart_7.bmp", "resources/towers/monkey/dart_8.bmp"
        };
        UpgradePrice[0] = 180;
        UpgradePrice[1] = 80;
        SetDamageType(DamageType::Normal);
    }

    void DartMonkey::Shoot(Vector2 target)
    {
        Tower::Shoot(target);
        Vector2 targetDirection = {
            (target.X - GetCenter().X), target.Y - GetCenter().Y
        };
        throwables.back()->SetSpeed(20);
        throwables.back()->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDirection));
        this->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDirection));
    }

    void DartMonkey::PushThrowablePool()
    {
        auto dart = make_shared<Throwable>(Throwable());
        dart->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
        dart->SetSpeed(5);
        throwablePool.push(dart);
    }

    void DartMonkey::Upgrade(int level)
    {
        Tower::Upgrade(level);
        switch (level)
        {
        case 0:
            SetMaxPop(2);
            break;
        case 1:
            _range = 180;
            break;
        default:
            break;
        }
        IsUpgrade[level] = true;
    }
}
