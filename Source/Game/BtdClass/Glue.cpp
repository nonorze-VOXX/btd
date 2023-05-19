#include "stdafx.h"
#include "Glue.h"

namespace Btd
{
    Glue::Glue()
    {
        _range = 37;
        throwable.SetMaxPop(20);
        throwable.SetMaxExistTime(-1);
        throwable.SetCantHtBloonTime(9999999); // a glue only hit a bloon once
    }
}
