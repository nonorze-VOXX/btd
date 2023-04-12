#include "stdafx.h"
#include "Boomerang.h"


using namespace Btd;

void Boomerang::Move()
{
    _position = BezierCurve4Point(route, BezierTime);
    SetTopLeft(static_cast<int>(_position.X), static_cast<int>(_position.Y));
    BezierTime += static_cast<float>(0.05);
    if (BezierTime > 1)
    {
        SetActive(false);
    }
}

void Boomerang::SetRoute(vector<Vector2> routes)
{
    route = routes;
    BezierTime = 0;
}
