#include "stdafx.h"
#include "Spikes.h"

namespace Btd
{
    Spikes::Spikes()
    {
        throwable.SetMaxExistTime(-1);
        throwable.SetCantHtBloonTime(0);
        throwable.SetMaxPop(10);
        _range = 25;
    }
}
