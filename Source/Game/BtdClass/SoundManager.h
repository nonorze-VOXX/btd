#pragma once
#include "BtdUtil.h"

namespace Btd
{
    
    class SoundManager
    {
    public:
        static void Init();
        static void musicStop(BtdSound type);
        static void musicPlay(BtdSound type,bool loop);
        static bool mute;
        
    };
}
