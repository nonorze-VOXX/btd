#include "stdafx.h"
#include "Super.h"

namespace Btd
{
    Super::Super()
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

    void Super::Shoot(Vector2 target)
    {
        Tower::Shoot(target);
        Vector2 targetDirection = {
            (target.X - GetCenter().X), target.Y - GetCenter().Y
        };
        throwables.back()->SetSpeed(20);
        throwables.back()->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDirection));
        this->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDirection));
    }
    void Super::PushThrowablePool()
    {
        auto dart = make_shared<Throwable>(Throwable());
        dart->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
        dart->SetSpeed(5);
        throwablePool.push(dart);
    }

    void Super::Upgrade(int level)
    {
        Tower::Upgrade(level);
        switch (level)
        {
        case 0:
            SetMaxPop(2);
            break;
        case 1:
            _range = 180;
            RangeCircle.SetCenter(static_cast<int>(GetCenter().X) - (_range - 100),
                                  static_cast<int>(GetCenter().Y) - (_range - 100));
            break;
        default:
            break;
        }
        IsUpgrade[level] = true;
    }
}
