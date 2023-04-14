#include "stdafx.h"
#include "BoomerangMonkey.h"

#include <valarray>

#include "Boomerang.h"

void Btd::BoomerangMonkey::Shoot(Vector2 target)
{
    if (throwablePool.empty() || throwablePool.front()->GetActive())
    {
        PushThrowablePool();
    }
    auto BoomerangNext = dynamic_pointer_cast<Boomerang>(throwablePool.front());
    Vector2 targetDirection = {
        target.X - GetCenter().X, target.Y - GetCenter().Y
    };
    vector<Vector2> route = {{0, 0}, {100, -50}, {100, 300}, {0, 0}};
    const float angle = atan2(targetDirection.X, targetDirection.Y);
    for (int i = 0; i < 4; i++)
    {
        route[i] = Spin(route[i], angle);
        route[i] = Vector2Add(GetCenter(), route[i]);
    }

    BoomerangNext->SetRoute(route);
    Tower::Shoot(target);
}

void Btd::BoomerangMonkey::PushThrowablePool()
{
    auto boomerang = make_shared<Boomerang>(Boomerang());
    boomerang->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
    boomerang->SetDamageType(DamageType::Normal);
    boomerang->SetRoute({{100, 500}, {500, 0}, {0, 500}, {100, 500}});
    throwablePool.push(boomerang);
}
