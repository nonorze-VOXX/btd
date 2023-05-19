#include "stdafx.h"
#include "SoundManager.h"
#include "../../Library/audio.h"

namespace Btd
{
    
    bool SoundManager::mute = false;

    void SoundManager::Init()
    {
        vector<string> soundName ;
        soundName.push_back("background.mp3");
        soundName.push_back("pop.mp3");
        soundName.push_back("lead.mp3");
        game_framework::CAudio *audio = game_framework::CAudio::Instance();
        for (int i =0 ;i< (int)soundName.size();i++)
        {
            string path = "Resources/sound/";
            string local = path+soundName[i];
            char* target = new char[local.length()+1];
            strcpy(target,local.c_str());
            audio->Load(i,target);
        }
    }

    void SoundManager::musicStop(BtdSound type)
    {
        game_framework::CAudio *audio = game_framework::CAudio::Instance();
        audio->Stop((int)type);
    }

    void SoundManager::musicPlay(BtdSound type, bool loop)
    {
        if(!mute)
        {
            game_framework::CAudio *audio = game_framework::CAudio::Instance();
            audio->Play((int)type, loop);
        }
    }
}
