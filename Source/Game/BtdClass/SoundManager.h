#pragma once
#include "BtdUtil.h"

#define soundTime 30
namespace Btd
{
    struct soundCounter
    {
        int counter;
        BtdSound type;
        int index;
        bool loop;
    };
    class SoundManager
    {
        static int index;
        static vector<soundCounter> soundTimePool;
        static vector<string> soundName ;
        static array<bool,4> soundUsed;
    public:
        static void Init();
        static void musicStop(BtdSound type);
        static void musicPlay(BtdSound type,bool loop);
        static void musicResume();
        static bool mute;
        static void Update();
        static soundCounter makeNewSound(BtdSound type, bool loop);
    };
}
