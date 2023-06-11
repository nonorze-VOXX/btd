#include "stdafx.h"
#include "Cannon.h"
#include "BloonFactory.h"
#include "Bomb.h"

namespace Btd
{
    Cannon::Cannon()
    {
        _range = 200;
        shootDeltaTime = 6;
        ThrowablePath = {"resources/towers/bomb/bomb.bmp", "resources/towers/bomb/bomb_1.bmp",
            "resources/towers/bomb/bomb_2.bmp", "resources/towers/bomb/bomb_3.bmp", "resources/towers/bomb/bomb_4.bmp"};
        UpgradePrice[0] = 380;
        UpgradePrice[1] = 180;
        SetDamageType(DamageType::Boom);
    }

    void Cannon::Shoot(Vector2 target)
    {
        Tower::Shoot(target);
        Vector2 targetDirection = {
            (target.X - GetCenter().X), target.Y - GetCenter().Y
        };
        this->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDirection));
    }

    void Cannon::PushThrowablePool()
    {
        auto bomb = make_shared<Bomb>(Bomb());
        bomb->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
        bomb->SetSpeed(8);
        throwablePool.push(bomb);
    }

    void Cannon::Upgrade(int level)
    {
        Tower::Upgrade(level);
        switch (level)
        {
        case 0:
            ThrowablePath = {"resources/towers/bomb/bomb.bmp", "resources/towers/bomb/bomb_1_big.bmp",
                                         "resources/towers/bomb/bomb_2_big.bmp", "resources/towers/bomb/bomb_3_big.bmp", "resources/towers/bomb/bomb_4_big.bmp"};
            break;
        case 1:
            _range = 250;
            RangeCircle.SetCenter(static_cast<int>(GetCenter().X) - (_range - 100),
                                  static_cast<int>(GetCenter().Y) - (_range - 100));
            break;
        default:
            break;
        }
        IsUpgrade[level] = true;
    }
}
