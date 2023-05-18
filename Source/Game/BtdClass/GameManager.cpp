#include "stdafx.h"
#include "GameManager.h"

#include "BloonFactory.h"
#include "TowerFactory.h"
#include "../../Library/audio.h"


namespace Btd
{
    void GameManager::OnBeginState()
    {
        BloonPause=false;
        GameFlow = Prepare;
        round = 0;
        TowerFactory::TowerVector.clear();
        TowerFactory::SpikesVector.clear();
        map->InitFactoryButton();
        BloonFactory::ClearActiveBloon();
        live = map->InitLives;
        money = map->InitMoney;
        db.LoadRounds();
        map->SetRounds(db.GetRounds());
        BloonFactory::SetNextRound(map->GetRounds()[round]);
        BloonFactory::RoundRoute = 0;
        IsLose = false;
        for(int i =0;i<8;i++){
            shortKeyMap['1'+i] = (Layer)i;
        }
    }

    void GameManager::OnInit()
    {
        vector<string> soundName ;
        soundName.push_back("background.mp3");
        soundName.push_back("pop.mp3");
        soundName.push_back("lead.mp3");
        game_framework::CAudio *audio = game_framework::CAudio::Instance();
        for (int i =0 ;i< (int)soundName.size();i++)
        {
            // TODO FIXME not sure if it memery leak
            string path = "Resources/sound/";
            string local = path+soundName[i];
            char* target = new char[local.length()+1];
            strcpy(target,local.c_str());
            audio->Load(i,target);
        }
        GameFlow = Prepare;
        startButton.LoadBitmapByString({"resources/start_button.bmp"});
        startButton.SetTopLeft(742, 620);
    }

    void GameManager::OnKeyUp(UINT, UINT, UINT)
    {
    }

    void GameManager::OnLButtonDown(UINT nFlags, CPoint point)
    {
        if((TowerFactory::TowerVector.empty() ||
            !TowerFactory::TowerVector.back()->IsMovable()) &&
            (TowerFactory::SpikesVector.empty() ||
            !TowerFactory::SpikesVector.back()->IsMovable()))
        {
            willDecreaseMoney = map->HandleButtonClicked(money);
        }
        
        money -= TowerFactory::HandleTowerClicked(money);

        // place tower
        if (!TowerFactory::TowerVector.empty() &&
            TowerFactory::TowerVector.back()->IsMovable() &&
            TowerFactory::TowerVector.back()->RangeCircle.GetFrameIndexOfBitmap() == 0)
        {
            money -= willDecreaseMoney;
            TowerFactory::TowerVector.back()->SetIsMove(false);
            TowerFactory::TowerVector.back()->SetActive(true);
        }

        // place spikes
        if (!TowerFactory::SpikesVector.empty() &&
             TowerFactory::SpikesVector.back()->tower.IsMovable() &&
            TowerFactory::SpikesVector.back()->tower.RangeCircle.GetFrameIndexOfBitmap() == 0)
        {
            money -= willDecreaseMoney;
            TowerFactory::SpikesVector.back()->SetIsMove(false);
            TowerFactory::SpikesVector.back()->SetActive(true);
        }
        switch (GameFlow)
        {
        case Prepare:
            {
                if (IsCursorInObj(startButton))
                {
                    GameFlow = Shoot;
                }
                break;
            }
        default:
            break;
        }
    }

    void GameManager::OnLButtonUp(UINT nFlags, CPoint point)
    {
    }

    void GameManager::OnMouseMove(UINT nFlags, CPoint point)
    {
        if (!TowerFactory::TowerVector.empty() &&
            TowerFactory::TowerVector.back()->IsMovable())
        {
            TowerFactory::TowerVector.back()->SetCenter(GetCursorPosX(),
                                                        GetCursorPosY());
        }
        if (!TowerFactory::SpikesVector.empty() &&
            TowerFactory::SpikesVector.back()->IsMovable())
        {
            TowerFactory::SpikesVector.back()->SetCenter(GetCursorPosX(),
                                                        GetCursorPosY());
        }
    }

    void GameManager::OnRButtonDown(UINT nFlags, CPoint point)
    {
    }

    void GameManager::OnRButtonUp(UINT nFlags, CPoint point)
    {
    }

    bool isOverlapOtherTower(GameObject t)
    {
        for (int i = 0; i < static_cast<int>(TowerFactory::TowerVector.size()) - 1; i++)
        {
            if (IsOverlap(*TowerFactory::TowerVector[i], t))
            {
                return true;
            }
        }
        return false;
    }

    void GameManager::OnMove()
    {
        if (!TowerFactory::TowerVector.empty())
        {
            if (map->IsOverLapRoad(static_cast<GameObject>(*TowerFactory::TowerVector.back())) ||
                map->IsOverSidebar(static_cast<GameObject>(*TowerFactory::TowerVector.back())) ||
                isOverlapOtherTower(static_cast<GameObject>(*TowerFactory::TowerVector.back())))
            {
                TowerFactory::TowerVector.back()->RangeCircle.SetFrameIndexOfBitmap(1);
            }
            else
            {
                TowerFactory::TowerVector.back()->RangeCircle.SetFrameIndexOfBitmap(0);
            }
        }
        if (!TowerFactory::SpikesVector.empty())
        {
            if (map->IsOverLapRoad(static_cast<GameObject>((*TowerFactory::SpikesVector.back()).tower)))
            {
                TowerFactory::SpikesVector.back()->tower.RangeCircle.SetFrameIndexOfBitmap(0);
            }
            else
            {
                TowerFactory::SpikesVector.back()->tower.RangeCircle.SetFrameIndexOfBitmap(1);
            }
        }
        map->UpdateFactoryButton();
        TowerFactory::UpdateSpikesVector();

        switch (GameFlow)
        {
        case Prepare:
            break;

        case Shoot:
            {
                bool RoundRunOut = BloonFactory::UpdateRound(BtdTimer.GetDeltaTime());
                bool isRoundEnd = BloonFactory::BloonVector.empty() && RoundRunOut;
                if (isRoundEnd)
                {
                    GameFlow = Win;
                }
                live -= BloonFactory::subLifeByGoalBloon();
                if (live <= 0)
                {
                    live = 0;
                    GameFlow = GameEnd;
                    IsLose = true;
                }
                break;
            }
        case Win:
            TowerFactory::SpikesVector.clear();
            round++;
            if (round >= static_cast<int>(map->GetRounds().size()))
            {
                GameFlow = GameEnd;
            }
            else
            {
                BloonFactory::SetNextRound(map->GetRounds()[round]);
                GameFlow = Prepare;
                money += 100;
            }

            break;
        case GameEnd:

            break;
        default: ;
        }
        for (auto& m : TowerFactory::TowerVector)
        {
            m->Update();
        }
        for (auto& s : TowerFactory::SpikesVector)
        {
            s->Update();
        }
        if(!BloonPause)
        {
        BloonFactory::UpdateBloon();
        }
    }

    void GameManager::OnShow()
    {
        map->ShowBackground();
        map->ShowRoad();
        map->ShowFactoryButton();
        for (int i = 0; i < static_cast<int>(TowerFactory::TowerVector.size()); i++)
        {
            TowerFactory::TowerVector[i]->HandleUpgradeBtnFrame(money);
            TowerFactory::TowerVector[i]->TowerShow();
        }
        for (int i=0; i<static_cast<int>(TowerFactory::SpikesVector.size()); i++)
        {
            TowerFactory::SpikesVector[i]->ShowBitmap();
        }
        for (auto& bloon : BloonFactory::BloonVector)
        {
            bloon.BloonShow();
        }
        switch (GameFlow)
        {
        case Prepare:
            startButton.ShowBitmap();
            break;
        default:
            break;
        }
    }

    bool GameManager::GetLose()
    {
        return IsLose;
    }

    void GameManager::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
        if((TowerFactory::TowerVector.empty() ||
            !TowerFactory::TowerVector.back()->IsMovable()) &&
            (TowerFactory::SpikesVector.empty() ||
            !TowerFactory::SpikesVector.back()->IsMovable()))
        {
            willDecreaseMoney = map->HandleShortCut(nChar,money);
        }
        if(shortKeyMap.find(nChar) != shortKeyMap.end())
        {
            BloonFactory::MakeBloon(shortKeyMap[nChar]);
        }
        switch (nChar)
        {
        case 'P':
            {
                live = 0;
                break;
            }
        case 'U':
            {
                BloonPause = !BloonPause;
                break;
            }
        case 'M':
            {
                money = 48763;
                break;
            }
        }
    }

    shared_ptr<Map> GameManager::map = make_shared<Map>(Map());
} // namespace Btd
