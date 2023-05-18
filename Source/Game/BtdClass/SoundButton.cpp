#include "stdafx.h"
#include "SoundButton.h"
#include "../../Library/audio.h"

namespace Btd
{
    
    void SoundButton::SetMute(bool status)
    {
        mute = status;
    }
    
    bool SoundButton::GetMute()
    {
        return mute;
    }

    void SoundButton::SwitchMute()
    {
        mute = !mute;
        SetFrameIndexOfBitmap(mute);
        game_framework::CAudio *audio = game_framework::CAudio::Instance();
        if(mute)
        {
            audio->Stop((int)BtdSound::BACKGROUND);
        }else
        {
            audio->Play((int)BtdSound::BACKGROUND,true);
        }
    }
}
