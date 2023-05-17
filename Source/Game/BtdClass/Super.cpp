#include "stdafx.h"
#include "Super.h"

namespace Btd
{
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
            break;
        default:
            break;
        }
        IsUpgrade[level] = true;
    }
}
