#include "stdafx.h"
#include "TestEverything.h"

#include "TowerFactory.h"

namespace Btd
{
    void TestEverything::UnitInit()
    {
        switch (_unitTestState)
        {
        case Bez:
            bezObject.LoadEmptyBitmap(100, 100);
            bezObject.SetTopLeft(0, 0);
            BezCounter = 0;

            break;


        default:
            break;
        }
    }

    void TestEverything::UnitTest()
    {
        switch (_unitTestState)
        {
        case Bez:
            auto position = BezierCurve4Point(
                {static_cast<float>(0), static_cast<float>(250)},
                {static_cast<float>(500), static_cast<float>(0)},
                {static_cast<float>(500), static_cast<float>(500)},
                {static_cast<float>(0), static_cast<float>(250)}, BezCounter);
            if (BezCounter >= 1)
            {
                BezDelta = -0.01F;
            }
            if (BezCounter <= 0)
            {
                BezDelta = 0.01F;
            }
            BezCounter = BezCounter + BezDelta;
            bezObject.SetTopLeft(static_cast<int>(position.X), static_cast<int>(position.Y));
            break;
        default: ;
        }
    }

    void TestEverything::UnitShow()
    {
        switch (_unitTestState)
        {
        case Bez:
            bezObject.ShowBitmap();
            break;
        default:
            break;
        }
    }
}
