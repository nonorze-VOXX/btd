#include "stdafx.h"
#include "TowerFactory.h"

#include "BoomerangMonkey.h"
#include "Spikes.h"
#include "Super.h"

vector<shared_ptr<Btd::Placeable>> Btd::TowerFactory::PlaceableVector = {};

void Btd::TowerFactory::MakeTower(TowerType attribute)
{
    vector<vector<string>> upgradeTextPath = {
        {"resources/towers/towers_upgrade_text/dart_upgrade_1.bmp", "resources/towers/towers_upgrade_text/dart_upgrade_2.bmp"},
        {"resources/towers/towers_upgrade_text/nail_upgrade_1.bmp", "resources/towers/towers_upgrade_text/nail_upgrade_2.bmp"},
        {"resources/towers/towers_upgrade_text/ice_upgrade_1.bmp", "resources/towers/towers_upgrade_text/ice_upgrade_2.bmp"},
        {"resources/towers/towers_upgrade_text/bomb_upgrade_1.bmp", "resources/towers/towers_upgrade_text/bomb_upgrade_2.bmp"},
        {"resources/towers/towers_upgrade_text/boomerang_upgrade_1.bmp", "resources/towers/towers_upgrade_text/boomerang_upgrade_2.bmp"},
        {"resources/towers/towers_upgrade_text/super_upgrade_1.bmp", "resources/towers/towers_upgrade_text/super_upgrade_2.bmp"},
   };
    int upgradeTextLocate[2][2] = {{750, 342}, {860, 342}};
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
            dartMonkey->UpgradeText[0].LoadBitmapByString({upgradeTextPath[0][0]}, RGB(0, 0, 0));
            dartMonkey->UpgradeText[1].LoadBitmapByString({upgradeTextPath[0][1]}, RGB(0, 0, 0));
            dartMonkey->UpgradeText[0].SetTopLeft(upgradeTextLocate[0][0], upgradeTextLocate[0][1]);
            dartMonkey->UpgradeText[1].SetTopLeft(upgradeTextLocate[1][0], upgradeTextLocate[1][1]);
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
            cannon->UpgradeText[0].LoadBitmapByString({upgradeTextPath[3][0]}, RGB(0, 0, 0));
            cannon->UpgradeText[1].LoadBitmapByString({upgradeTextPath[3][1]}, RGB(0, 0, 0));
            cannon->UpgradeText[0].SetTopLeft(upgradeTextLocate[0][0], upgradeTextLocate[0][1]);
            cannon->UpgradeText[1].SetTopLeft(upgradeTextLocate[1][0], upgradeTextLocate[1][1]);
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
            nailMachine ->UpgradeText[0].LoadBitmapByString({upgradeTextPath[1][0]}, RGB(0, 0, 0));
            nailMachine->UpgradeText[1].LoadBitmapByString({upgradeTextPath[1][1]}, RGB(0, 0, 0));
            nailMachine->UpgradeText[0].SetTopLeft(upgradeTextLocate[0][0], upgradeTextLocate[0][1]);
            nailMachine->UpgradeText[1].SetTopLeft(upgradeTextLocate[1][0], upgradeTextLocate[1][1]);
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
            ice->UpgradeText[0].LoadBitmapByString({upgradeTextPath[2][0]}, RGB(0, 0, 0));
            ice->UpgradeText[1].LoadBitmapByString({upgradeTextPath[2][1]}, RGB(0, 0, 0));
            ice->UpgradeText[0].SetTopLeft(upgradeTextLocate[0][0], upgradeTextLocate[0][1]);
            ice->UpgradeText[1].SetTopLeft(upgradeTextLocate[1][0], upgradeTextLocate[1][1]);
            TowerVector.push_back(ice);
            break;
        }
    case TowerType::super:
        {
            shared_ptr<Super> superMonkey = make_shared<Super>(Super());
            superMonkey->LoadBitmapByString({"resources/towers/super/tower_super_1.bmp", "resources/towers/super/tower_super_2.bmp"
                                               , "resources/towers/super/tower_super_3.bmp", "resources/towers/super/tower_super_4.bmp", "resources/towers/super/tower_super_5.bmp"
                                               , "resources/towers/super/tower_super_6.bmp", "resources/towers/super/tower_super_7.bmp", "resources/towers/super/tower_super_1.bmp"}, RGB(0, 0, 0));
            superMonkey->SetCenter(GetCursorPosX(), GetCursorPosY());
            superMonkey->SetIsMove(true);
            superMonkey->SetActive(false);
            superMonkey->SetFrameIndexOfBitmap(6);
            superMonkey->RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            superMonkey->RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            superMonkey->SetCollider({static_cast<float>(superMonkey->GetWidth())*0.4F,static_cast<float>(superMonkey->GetHeight())*0.4F});
            superMonkey->SetMaxPop(1);
            superMonkey->UpgradeText[0].LoadBitmapByString({upgradeTextPath[4][0]}, RGB(0, 0, 0));
            superMonkey->UpgradeText[1].LoadBitmapByString({upgradeTextPath[4][1]}, RGB(0, 0, 0));
            superMonkey->UpgradeText[0].SetTopLeft(upgradeTextLocate[0][0], upgradeTextLocate[0][1]);
            superMonkey->UpgradeText[1].SetTopLeft(upgradeTextLocate[1][0], upgradeTextLocate[1][1]);
            TowerVector.push_back(superMonkey);
            break;
        }
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
            boomerangMonkey->UpgradeText[0].LoadBitmapByString({upgradeTextPath[4][0]}, RGB(0, 0, 0));
            boomerangMonkey->UpgradeText[1].LoadBitmapByString({upgradeTextPath[4][1]}, RGB(0, 0, 0));
            boomerangMonkey->UpgradeText[0].SetTopLeft(upgradeTextLocate[0][0], upgradeTextLocate[0][1]);
            boomerangMonkey->UpgradeText[1].SetTopLeft(upgradeTextLocate[1][0], upgradeTextLocate[1][1]);
            TowerVector.push_back(boomerangMonkey);
            
        }
        
        break;
    case TowerType::spikes:
        {
            shared_ptr<Spikes> spikes = make_shared<Spikes>(Spikes());
            spikes->LoadBitmapByString({"resources/towers/spikes.bmp"}, RGB(255, 255, 255));
            spikes->SetCenter(GetCursorPosX(), GetCursorPosY());
            spikes->SetIsMove(true);
            spikes->SetActive(false);
            spikes->tower.RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            spikes->tower.RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            spikes->throwable.SetDamageType(DamageType::Normal);
            PlaceableVector.push_back(spikes);
        }
        break;
    case TowerType::glue:
        {
            shared_ptr<Glue> glue = make_shared<Glue>(Glue());
            glue->LoadBitmapByString({"resources/towers/glue.bmp"}, RGB(255, 255, 255));
            glue->SetCenter(GetCursorPosX(), GetCursorPosY());
            glue->SetIsMove(true);
            glue->SetActive(false);
            glue->throwable.SetDamageType(DamageType::Glue);
            glue->tower.RangeCircle.LoadBitmapByString({"resources/towers/range.bmp", "resources/towers/range_red.bmp"}, RGB(0, 0, 0));
            glue->tower.RangeCircle.SetCenter(GetCursorPosX(), GetCursorPosY());
            PlaceableVector.push_back(glue);
        }      
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
    for (int i=static_cast<int>(PlaceableVector.size())-1; i>=0; i--)
    {
        if (PlaceableVector[i]->tower.IsMovable() == false &&
            PlaceableVector[i]->throwable.GetActive() == false)
        {
            PlaceableVector.erase(PlaceableVector.begin() + i);
        }
    }
}

