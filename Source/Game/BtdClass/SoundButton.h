#pragma once
#include "Button.h"

namespace Btd
{
    class SoundButton :public Button
    {
    public:
        void SetMute(bool status);
        bool GetMute();
        void SwitchMute();

    private:
        bool mute;
    };
}
