#include "stdafx.h"
#include "SoundButton.h"

#include "SoundManager.h"
#include "../../Library/audio.h"

namespace Btd
{
    
    
    void SoundButton::SwitchMute()
    {
        SoundManager::mute = !SoundManager::mute;
        SetFrameIndexOfBitmap(SoundManager::mute);
        if(SoundManager::mute)
        {
            SoundManager::musicStop(BtdSound::BACKGROUND);
        }else
        {
            SoundManager::musicPlay(BtdSound::BACKGROUND,true);
        }
    }
}
