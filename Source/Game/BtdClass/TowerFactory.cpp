#include "stdafx.h"
#include "TowerFactory.h"

#include "BoomerangMonkey.h"
#include "Spikes.h"

vector<shared_ptr<Btd::Spikes>> Btd::TowerFactory::SpikesVector = {};

void Btd::TowerFactory::MakeTower(TowerType attribute)
{
    switch (attribute)
    {
    case TowerType::dart:
        {
            shared_ptr<DartMonkey> dartMonkey = make_shared<DartMonkey>(DartMonkey());
            dartMonkey->LoadBitmapByString({"resources/towers/monkey/tower_monkey_1.bmp", "resources/towers/monkey/tower_monkey_2.bmp"
                                               , "resources/towers/monkey/tower_monkey_3.bmp", "resources/towers/monkey/tower_monkey_4.bmp", "resources/towers/monkey/tower_monkey_5.bmp"
                                               , "resources/towers/monkey/tower_monkey_6.bmp", "resources/towers/monkey/tower_monkey_7.bmp", "resources/towers/monkey/tower_monkey_8.bmp"}, RGB(0, 0, 0));
            dartMonkey->SetCenter(GetCursorPosX(), GetCursorPosY());
            dartMonkey->SetIsMove(true);
            dartMonkey->SetActive(false);
            dartMonkey->SetFrameIndexOfBitmap(6);
            dartMonkey->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            dartMonkey->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            dartMonkey->SetCollider({static_cast<float>(dartMonkey->GetWidth())*0.4F,static_cast<float>(dartMonkey->GetHeight())*0.4F});
            dartMonkey->SetMaxPop(1);
            TowerVector.push_back(dartMonkey);
            break;
        }
    case TowerType::bomb:
        {
            shared_ptr<Cannon> cannon = make_shared<Cannon>(Cannon());
            cannon->LoadBitmapByString({"resources/towers/bomb/tower_bomb_1.bmp", "resources/towers/bomb/tower_bomb_2.bmp"
                                           , "resources/towers/bomb/tower_bomb_3.bmp", "resources/towers/bomb/tower_bomb_4.bmp", "resources/towers/bomb/tower_bomb_5.bmp"
                                           , "resources/towers/bomb/tower_bomb_6.bmp", "resources/towers/bomb/tower_bomb_7.bmp", "resources/towers/bomb/tower_bomb_8.bmp"}, RGB(255, 255, 255));
            cannon->SetCenter(GetCursorPosX(), GetCursorPosY());
            cannon->SetIsMove(true);
            cannon->SetActive(false);
            cannon->SetFrameIndexOfBitmap(6);
            cannon->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            cannon->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            cannon->SetCollider({30,30});
            TowerVector.push_back(cannon);
            break;
        }
    case TowerType::nail:
        {
            shared_ptr<NailMachine> nailMachine = make_shared<NailMachine>(NailMachine());
            nailMachine->LoadBitmapByString({"resources/towers/nail/tower_nail.bmp"}, RGB(0, 0, 0));
            nailMachine->SetCenter(GetCursorPosX(), GetCursorPosY());
            nailMachine->SetIsMove(true);
            nailMachine->SetActive(false);
            nailMachine->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            nailMachine->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            nailMachine->SetCollider({static_cast<float>(nailMachine->GetWidth())*0.4F,static_cast<float>(nailMachine->GetHeight())*0.4F});
            nailMachine->SetMaxPop(1);
            TowerVector.push_back(nailMachine);
            break;
        }
    case TowerType::ice:
        {
            shared_ptr<IceTower> ice = make_shared<IceTower>(IceTower());
            ice->LoadBitmapByString({"resources/towers/ice/tower_ice.bmp"}, RGB(0, 0, 0));
            ice->SetCenter(GetCursorPosX(), GetCursorPosY());
            ice->SetIsMove(true);
            ice->SetActive(false);
            ice->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            ice->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            TowerVector.push_back(ice);
        }
    case TowerType::super:
        break;
    case TowerType::boomerang:
        {
            shared_ptr<BoomerangMonkey> boomerangMonkey = make_shared<BoomerangMonkey>(BoomerangMonkey());
            boomerangMonkey->LoadBitmapByString({
                "resources/towers/boomerang/BoomerangTower_1.bmp", "resources/towers/boomerang/BoomerangTower_2.bmp",
                "resources/towers/boomerang/BoomerangTower_3.bmp", "resources/towers/boomerang/BoomerangTower_4.bmp",
                "resources/towers/boomerang/BoomerangTower_5.bmp", "resources/towers/boomerang/BoomerangTower_6.bmp",
                "resources/towers/boomerang/BoomerangTower_7.bmp", "resources/towers/boomerang/BoomerangTower_8.bmp"
            }, RGB(255,255,255));
            boomerangMonkey->SetFrameIndexOfBitmap(6);
            boomerangMonkey->SetCenter(GetCursorPosX(), GetCursorPosY());
            boomerangMonkey->SetIsMove(true);
            boomerangMonkey->SetActive(false);
            boomerangMonkey->SetShootDeltaTime(3);
            boomerangMonkey->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            boomerangMonkey->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            boomerangMonkey->SetCollider({static_cast<float>(boomerangMonkey->GetWidth()),static_cast<float>(boomerangMonkey->GetHeight())});
            boomerangMonkey->SetMaxPop(2);
            TowerVector.push_back(boomerangMonkey);
            
        }
        
        break;
    case TowerType::spikes:
        {
            shared_ptr<Spikes> spikes = make_shared<Spikes>(Spikes());
            spikes->LoadBitmapByString({"resources/towers/spikes.bmp"}, RGB(255, 255, 255));
            spikes->SetCenter(GetCursorPosX(), GetCursorPosY());
            spikes->SetFrameIndexOfBitmap(0);
            spikes->SetIsMove(true);
            spikes->SetActive(false);
            spikes->tower.RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            spikes->tower.RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            SpikesVector.push_back(spikes);
        }
        break;
    default:
        break;
    }
}

bool handleUpgradeButtonClicked (int towerIndex, int money, int *willDecreaseMoney)
{
    bool isBtnClicked = false;
    for (int i=0; i<2; i++)
    {
        if (Btd::TowerFactory::TowerVector[towerIndex]->IsClicked() &&
            Btd::TowerFactory::TowerVector[towerIndex]->UpgradeBtn[i].IsCursorFocus())
        // upgrade btn clicked
        {
            isBtnClicked = true;
            if (!Btd::TowerFactory::TowerVector[towerIndex]->IsUpgrade[i] &&
                Btd::TowerFactory::TowerVector[towerIndex]->UpgradePrice[i] <= money)
            // can upgrade
            {
                Btd::TowerFactory::TowerVector[towerIndex]->Upgrade(i);
                (*willDecreaseMoney) += Btd::TowerFactory::TowerVector[towerIndex]->UpgradePrice[i];
            }
        }
    }
    return  isBtnClicked;
}

int Btd::TowerFactory::HandleTowerClicked(int money)
{
    int willDecreaseMoney = 0;
    for (int i=0; i<(int)TowerVector.size(); i++)
    {
        if (TowerVector[i]->IsCursorFocus() ||
            handleUpgradeButtonClicked(i, money, &willDecreaseMoney))
        {
            TowerVector[i]->SetClicked(true);
        }
        else
        {
            TowerVector[i]->SetClicked(false);
        }
    }
    return willDecreaseMoney;
}

void Btd::TowerFactory::UpdateSpikesVector()
{
    for (int i=static_cast<int>(SpikesVector.size())-1; i>=0; i--)
    {
        if (SpikesVector[i]->tower.IsMovable() == false &&
            SpikesVector[i]->throwable.GetActive() == false)
        {
            SpikesVector.erase(SpikesVector.begin() + i);
        }
    }
}
