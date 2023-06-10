#include "stdafx.h"
#include "GameManager.h"

#include "BloonFactory.h"
#include "SoundManager.h"
#include "TowerFactory.h"
#include "../../Library/audio.h"


namespace Btd
{
    void GameManager::OnBeginState()
    {
        gameOverCounter=0;
        BloonPause=false;
        GameFlow =GameFlow::Prepare;
        round = 0;
        TowerFactory::TowerVector.clear();
        TowerFactory::PlaceableVector.clear();
        map->InitFactoryButton();
        BloonFactory::ClearActiveBloon();
        live = map->InitLives;
        money = map->InitMoney;
        map->SetRounds(db.GetRounds());
        BloonFactory::SetNextRound(map->GetRounds()[round]);
        BloonFactory::RoundRoute = 0;
        TowerFactory::SetPriceTable(map->GetPriceTable());
        IsLose = false;
        IsWin = false;
        for(int i =0;i<8;i++){
            shortKeyMap['1'+i] = (Layer)i;
        }
    }

    void GameManager::OnInit()
    {
        db.LoadRounds();
        SoundManager::Init();
        GameFlow =GameFlow::Prepare;
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
            (TowerFactory::PlaceableVector.empty() ||
            !TowerFactory::PlaceableVector.back()->IsMovable()) )
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
        if (!TowerFactory::PlaceableVector.empty() &&
             TowerFactory::PlaceableVector.back()->tower.IsMovable() &&
            TowerFactory::PlaceableVector.back()->tower.RangeCircle.GetFrameIndexOfBitmap() == 0)
        {
            money -= willDecreaseMoney;
            TowerFactory::PlaceableVector.back()->SetIsMove(false);
            TowerFactory::PlaceableVector.back()->SetActive(true);
        }
        
        
        switch (GameFlow)
        {
        case GameFlow::Prepare:
            {
                if (IsCursorInObj(startButton))
                {
                    GameFlow = GameFlow::Shoot;
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
        if (!TowerFactory::PlaceableVector.empty() &&
            TowerFactory::PlaceableVector.back()->IsMovable())
        {
            TowerFactory::PlaceableVector.back()->SetCenter(GetCursorPosX(),
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
        if(GetLose())
        {
            gameOverCounter++;
        }
        SoundManager::Update();
        // tower range circle
        if (!TowerFactory::TowerVector.empty())
        {
            if (TowerFactory::TowerVector.back()->IsMovable())
            {
                if (map->IsOverLapRoad(static_cast<GameObject>(*TowerFactory::TowerVector.back())) ||
                    map->IsOverSidebar(static_cast<GameObject>(*TowerFactory::TowerVector.back())) ||
                    isOverlapOtherTower(static_cast<GameObject>(*TowerFactory::TowerVector.back()))                    )
                {
                    TowerFactory::TowerVector.back()->RangeCircle.SetFrameIndexOfBitmap(1);
                }
                else
                {
                    TowerFactory::TowerVector.back()->RangeCircle.SetFrameIndexOfBitmap(0);
                }
            }
        }
        // spikes range circle
        if (!TowerFactory::PlaceableVector.empty())
        {
            if (map->IsOverLapRoad(static_cast<GameObject>((*TowerFactory::PlaceableVector.back()).tower)))
            {
                TowerFactory::PlaceableVector.back()->tower.RangeCircle.SetFrameIndexOfBitmap(0);
            }
            else
            {
                TowerFactory::PlaceableVector.back()->tower.RangeCircle.SetFrameIndexOfBitmap(1);
            }
        }
        map->UpdateFactoryButton();
        TowerFactory::UpdateSpikesVector();

        switch (GameFlow)
        {
        case GameFlow::Prepare:
            BloonFactory::SetNextRound(map->GetRounds()[round]);
            break;

        case GameFlow::Shoot:
            {
                bool RoundRunOut = BloonFactory::UpdateRound(BtdTimer.GetDeltaTime());
                bool isRoundEnd = BloonFactory::BloonVector.empty() && RoundRunOut;
                if (isRoundEnd)
                {
                    GameFlow = GameFlow::Win;
                }
                live -= BloonFactory::subLifeByGoalBloon();
                if (live <= 0)
                {
                    live = 0;
                    GameFlow = GameFlow::GameEnd;
                    IsLose = true;
                }
                break;
            }
        case GameFlow::Win:
            TowerFactory::PlaceableVector.clear();
            round++;
            if (round >= static_cast<int>(map->GetRounds().size()))
            {
                GameFlow = GameFlow::GameEnd;
                IsWin = true;
                db.PassMap(map->GetMapType());
            }
            else
            {
                GameFlow = GameFlow::Prepare;
                money += int(sqrt(round) * 70);
            }

            break;
        case GameFlow::GameEnd:

            break;
        default: ;
        }
        for (auto& m : TowerFactory::TowerVector)
        {
            m->Update();
        }
        for (auto& s : TowerFactory::PlaceableVector)
        {
            s->Update();
        }
        if(!BloonPause)
        {
            int increaseMoney = 0;
            BloonFactory::UpdateBloon(&increaseMoney);
            money += increaseMoney;
        }
    }

    void GameManager::OnShow()
    {
        map->ShowBackground();
        map->ShowRoad();
        for (int i = 0; i < static_cast<int>(TowerFactory::TowerVector.size()); i++)
        {
            TowerFactory::TowerVector[i]->HandleUpgradeBtnFrame(money);
            TowerFactory::TowerVector[i]->TowerShow();
        }
        for (int i=0; i<static_cast<int>(TowerFactory::PlaceableVector.size()); i++)
        {
            TowerFactory::PlaceableVector[i]->ShowBitmap();
        }
        map->ShowFactoryButton();
        for (auto& bloon : BloonFactory::BloonVector)
        {
            bloon.BloonShow();
        }
        switch (GameFlow)
        {
        case GameFlow::Prepare:
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

    bool GameManager::GetWin()
    {
        return IsWin;
    }

    bool GameManager::GetGoToInit()
    {
        return (GetLose()&&gameOverCounter>=170)||GetWin();
    }

    vector<GameText> GameManager::GetGameText()
    {
        vector<GameText> texts;
        texts.push_back({"Round:   "+to_string(GetRound()+1),{749,25},RGB(255,255,255),27});
        texts.push_back({"Money: "+to_string(GetMoney()),{749,61},RGB(255,255,255),27});
        texts.push_back({"Lives:  "+to_string(GetLive()),{749,97},RGB(255,255,255),27});

        texts.push_back({"Build Towers",{749,152},RGB(255,255,255),24});
        texts.push_back({"____________",{749,152},RGB(255,255,255),24});

        if(GetLose())
        {
            Vector2 screenCenter = {(float)SCREEN_SIZE_X/2,(float)SCREEN_SIZE_Y/2};
            Vector2 TextPosition = Vector2Sub(screenCenter,{ (float)(2.5 *gameOverCounter), (float)gameOverCounter });
            float offset = (float)gameOverCounter /30.f;
            texts.push_back({"game over", Vector2Add(TextPosition,{offset,0}),RGB(255,255,255),gameOverCounter});
            texts.push_back({"game over", Vector2Add(TextPosition,{0,offset}),RGB(255,255,255),gameOverCounter});
            texts.push_back({"game over", Vector2Add(TextPosition,{-offset,0}),RGB(255,255,255),gameOverCounter});
            texts.push_back({"game over", Vector2Add(TextPosition,{0,-offset}),RGB(255,255,255),gameOverCounter});
            texts.push_back({"game over", TextPosition,RGB(0,0,0),gameOverCounter});
        }
        return texts;
    }

    void GameManager::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
        if((TowerFactory::TowerVector.empty() ||
            !TowerFactory::TowerVector.back()->IsMovable()) &&
            (TowerFactory::PlaceableVector.empty() ||
            !TowerFactory::PlaceableVector.back()->IsMovable()))
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
        case 'N':
            if (round < static_cast<int>(map->GetRounds().size() - 1))
                round ++;
        case 0x1B: //esc
            if (!TowerFactory::TowerVector.empty() && TowerFactory::TowerVector.back()->IsMovable())
            {
                TowerFactory::TowerVector.pop_back();
            }
            else if (!TowerFactory::PlaceableVector.empty() && TowerFactory::PlaceableVector.back()->IsMovable())
            {
                TowerFactory::PlaceableVector.pop_back();
            }
            break;
        }
    }

    shared_ptr<Map> GameManager::map = make_shared<Map>(Map());
} // namespace Btd
