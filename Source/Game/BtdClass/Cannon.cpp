#include "stdafx.h"
#include "Cannon.h"
#include "BloonFactory.h"
#include "Bomb.h"

namespace Btd
{
    void Cannon::Shoot(Vector2 target)
    {
        Tower::Shoot(target);
        // Vector2 targetDir = {target.X - GetCenter().X, target.Y - GetCenter().Y};
        // this->SetFrameIndexOfBitmap(GetFrameIndexByVector2(targetDir));
    }

    void Cannon::PushThrowablePool()
    {
        auto bomb = make_shared<Bomb>(Bomb());
        bomb->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
        bomb->SetSpeed(5);
        bomb->SetDamageType(DamageType::Boom);
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
            break;
        default:
            break;
        }
        IsUpgrade[level] = true;
    }
}
