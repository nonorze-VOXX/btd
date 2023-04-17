#include "stdafx.h"
#include "BoomerangMonkey.h"

#include <valarray>

#include "Boomerang.h"

void Btd::BoomerangMonkey::UpdateThrowable()
{
    for (int i = static_cast<int>(throwables.size()) - 1; i >= 0; i--)
    {
        dynamic_pointer_cast<Boomerang>(throwables[i])->Update();
        if (Vector2Distance(throwables[i]->GetCenter(), GetCenter()) > static_cast<float>(_range) + 70)
        {
            // if throwable fly over (range + 70) distance will be erase
            throwables[i]->SetActive(false);
        }
        if (!throwables[i]->GetActive())
        {
            throwables.erase(throwables.begin() + i);
        }
    }
}

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
    vector<Vector2> route = {{0, 0}, {500, 200}, {200, -600}, {0, 0}};
    const float angle = -atan2(-targetDirection.Y, targetDirection.X);//space angke transform
    const float scale = (float) _range/300.F; //origin route is use 300 range generate
    for (int i = 0; i < 4; i++)
    {
        route[i] = Spin(route[i], angle);
        route[i] = Scale(route[i],scale);
        route[i] = Vector2Add(GetCenter(), route[i]);
    }

    BoomerangNext->SetRoute(route);
    BoomerangNext->SetPenetrate(true);
    BoomerangNext->SetMaxExistTime(1000000);
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
