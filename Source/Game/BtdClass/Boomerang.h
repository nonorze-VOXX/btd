#pragma once
#include "Throwable.h"

namespace Btd
{
    class Boomerang : public Throwable
    {
    private:
        vector<Vector2> route;
        float BezierTime = 0;

    public:
        void Move() override;
        void SetRoute(vector<Vector2> routes);
    };
}
