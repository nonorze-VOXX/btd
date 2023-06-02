#include "StdAfx.h"

#include "string"
#include "vector"

#include "BtdUtil.h"
#include "GameObject.h"
#include "map.h"

#include "SoundManager.h"

namespace Btd
{
    void Map::SetRoutesByMap(MapType type)
    {
        Vector2 mapSize = {
            static_cast<float>(GetBackground().GetWidth()),
            static_cast<float>(GetBackground().GetHeight())
        };
        switch (type)
        {
        case MapType::easy:
            SetRoute({
                {
                    {mapSize.X * -0.05F, mapSize.Y * 0.5F},
                    {mapSize.X * 0.29F, mapSize.Y * 0.5F},
                    {mapSize.X * 0.29F, mapSize.Y * 0.25F},
                    {mapSize.X * 0.17F, mapSize.Y * 0.25F},
                    {mapSize.X * 0.17F, mapSize.Y * 0.08F},
                    {mapSize.X * 0.65F, mapSize.Y * 0.08F},
                    {mapSize.X * 0.65F, mapSize.Y * 0.25F},
                    {mapSize.X * 0.45F, mapSize.Y * 0.25F},
                    {mapSize.X * 0.45F, mapSize.Y * 0.43F},
                    {mapSize.X * 0.65F, mapSize.Y * 0.43F},
                    {mapSize.X * 0.65F, mapSize.Y * 0.62F},
                    {mapSize.X * 0.16F, mapSize.Y * 0.62F},
                    {mapSize.X * 0.16F, mapSize.Y * 0.9F},
                    {mapSize.X * 0.35F, mapSize.Y * 0.9F},
                    {mapSize.X * 0.35F, mapSize.Y * 0.75F},
                    {mapSize.X * 0.55F, mapSize.Y * 0.75F},
                    {mapSize.X * 0.55F, mapSize.Y * 1.0F},
                }
            });
            break;
        case MapType::medium:
            SetRoute({
                {
                    {mapSize.X * 0.12F, mapSize.Y * -0.05F},
                    {mapSize.X * 0.12F, mapSize.Y * 0.41F},
                    {mapSize.X * 0.26F, mapSize.Y * 0.41F},
                    {mapSize.X * 0.26F, mapSize.Y * 0.62F},
                    {mapSize.X * 0.11F, mapSize.Y * 0.62F},
                    {mapSize.X * 0.11F, mapSize.Y * 0.83F},
                    {mapSize.X * 0.39F, mapSize.Y * 0.83F},
                    {mapSize.X * 0.39F, mapSize.Y * 0.21F},
                    {mapSize.X * 0.67F, mapSize.Y * 0.21F},
                    {mapSize.X * 0.67F, mapSize.Y * 0.41F},
                    {mapSize.X * 0.52F, mapSize.Y * 0.41F},
                    {mapSize.X * 0.52F, mapSize.Y * 0.61F},
                    {mapSize.X * 0.65F, mapSize.Y * 0.61F},
                    {mapSize.X * 0.65F, mapSize.Y * 1.02F},
                }
            });
            break;
        case MapType::hard:
            SetRoute({
                {
                    {mapSize.X * 0.47F, mapSize.Y * -0.03F},
                    {mapSize.X * 0.47F, mapSize.Y * 0.15F},
                    {mapSize.X * 0.63F, mapSize.Y * 0.15F},
                    {mapSize.X * 0.63F, mapSize.Y * 0.38F},
                    {mapSize.X * 0.37F, mapSize.Y * 0.38F},
                    {mapSize.X * 0.37F, mapSize.Y * 0.18F},
                    {mapSize.X * 0.24F, mapSize.Y * 0.18F},
                    {mapSize.X * 0.24F, mapSize.Y * 0.66F},
                    {mapSize.X * 0.13F, mapSize.Y * 0.66F},
                    {mapSize.X * 0.13F, mapSize.Y * 0.84F},
                    {mapSize.X * 0.22F, mapSize.Y * 0.84F},
                    {mapSize.X * 0.22F, mapSize.Y * 1.03F},
                },
                {
                    {mapSize.X * 0.09F, mapSize.Y * -0.03F},
                    {mapSize.X * 0.09F, mapSize.Y * 0.52F},
                    {mapSize.X * 0.425F, mapSize.Y * 0.52F},
                    {mapSize.X * 0.425F, mapSize.Y * 0.70F},
                    {mapSize.X * 0.54F, mapSize.Y * 0.70F},
                    {mapSize.X * 0.54F, mapSize.Y * 0.52F},
                    {mapSize.X * 0.66F, mapSize.Y * 0.52F},
                    {mapSize.X * 0.66F, mapSize.Y * 0.90F},
                    {mapSize.X * 0.35F, mapSize.Y * 0.9F},
                    {mapSize.X * 0.35F, mapSize.Y * 1.01F},
                }
            });
            break;
        default: ;
        }
    }


    void Map::InitRoad(MapType type)
    {
        int roadSize[3];
        string roadPath[3] = {"easy", "medium", "hard"};
        vector<Vector2> location[3] =
        {
            {
                {0, 340}, {248, 143}, {131, 140},
                {132, 26}, {132, 22}, {604, 23},
                {414, 152}, {415, 155}, {412, 288},
                {617, 288}, {138, 436}, {141, 436},
                {144, 652}, {327, 510}, {327, 512},
                {502, 507}
            },
            {
                {89, 0}, {123, 276}, {221, 312}, {71, 435},
                {70, 479}, {119, 591}, {351, 121}, {392, 120},
                {630, 161}, {487, 279}, {485, 322}, {525, 436},
                {616, 483}, 
            },
            {
                {48, 0}, {113, 364}, {382, 403}, {386, 500},
                {498, 354}, {542, 357}, {615, 398}, {303, 644},
                {305, 692}, {430, 0}, {475, 85}, {586, 134},
                {333, 251}, {331, 90}, {196, 92}, {196, 89},
                {80, 476}, {79, 515}, {106, 596}, {186, 625}
            }
        };
        for (int i = 0; i < 3; i++)
        {
            roadSize[i] = static_cast<int>(location[i].size());
        }
        for (int i = 0; i < roadSize[(int)type]; i++)
        {
            GameObject tmpRoad;
            string filePath = "resources/map/" + roadPath[(int)type] + "/roads/road_" + std::to_string(i + 1) + ".bmp";
            tmpRoad.LoadBitmapByString({filePath});
            // tmpRoad.SetHeight(tmpRoad.GetHeight() - 10);
            // tmpRoad.SetWidth(tmpRoad.GetWidth() - 10);
            tmpRoad.SetTopLeft(static_cast<int>(location[(int)type][i].X), static_cast<int>(location[(int)type][i].Y));
            tmpRoad.SetTag("road");
            _road.push_back(tmpRoad);
        }
        _sidebar.LoadBitmapByString({"resources/map/" + roadPath[(int)type] + "/sidebar.bmp"});
        _sidebar.SetTopLeft(732, 11);

        priceTable = {0, 0, 0, 0, 0, 0, 0, 0};
        priceTable[(int)TowerType::bomb] = 520;
        priceTable[(int)TowerType::boomerang] = 475;
        priceTable[(int)TowerType::dart] = 250;
        priceTable[(int)TowerType::spikes] = 25;
        priceTable[(int)TowerType::glue] = 35;
        priceTable[(int)TowerType::ice] = 385;
        priceTable[(int)TowerType::nail] = 340;
        priceTable[(int)TowerType::super] = 3600;
    }

    void Map::ShowRoad()
    {
        for (int i = 0; i < static_cast<int>(_road.size()); i++)
        {
            _road[i].ShowBitmap();
        }
        _sidebar.ShowBitmap();
    }

    void Map::InitBackground(MapType type)
    {
        vector<string> backGroundPath[3] = {
            {"resources/map/easy/map.bmp"},
            {"resources/map/medium/map.bmp"},
            {"resources/map/hard/map.bmp"},
        };
        _background.LoadBitmapByString(backGroundPath[(int)type]);
        _background.SetTopLeft(0, 0);
    }

    void Map::ShowBackground()
    {
        _background.ShowBitmap();
    }

    void Map::InitFactoryButton()
    {
        buttonNumber = 8;
        vector<string> filePath = {
            "resources/button/button_monkey.bmp", "resources/button/button_nail.bmp", "resources/button/button_ice.bmp",
            "resources/button/button_bomb.bmp", "resources/button/button_spikes.bmp", "resources/button/button_glue.bmp"
            , "resources/button/button_boomerang.bmp", "resources/button/button_super.bmp"
        };
        vector<string> infoPath = {
            "resources/towers/towers_info/dart_info.bmp", "resources/towers/towers_info/nail_info.bmp", "resources/towers/towers_info/ice_info.bmp",
            "resources/towers/towers_info/cannon_info.bmp", "resources/towers/towers_info/spikes_info.bmp", "resources/towers/towers_info/glue_info.bmp",
            "resources/towers/towers_info/boomerang_info.bmp", "resources/towers/towers_info/super_info.bmp",
        };
        vector<TowerType> attributes = {
            TowerType::dart, TowerType::nail, TowerType::ice, TowerType::bomb,
            TowerType::spikes, TowerType::glue, TowerType::boomerang, TowerType::super};
        float start = 750, space = 56;
        vector<Vector2> locations = {
            {start, 192}, {start + space * 1, 192}, {start + space * 2, 192},
            {start + space * 3, 192}, {start, 192 + space} ,
            {start + space * 1 , 192+space}, {start + space * 2, 192 + space},
            {start + space * 3, 192 + space}
        };
        for (int i = 0; i < buttonNumber; i++)
        {
            FactoryButton factoryButton =FactoryButton();
            factoryButton.LoadBitmapByString({filePath[i]},RGB(255,255,255));
            factoryButton.SetAttribute(attributes[i]);
            factoryButton.SetTopLeft(static_cast<int>(locations[i].X), static_cast<int>(locations[i].Y));
            factoryButton.TowerInfo.LoadBitmapByString({infoPath[i]});
            factoryButton.TowerInfo.SetTopLeft(750, 342);
            _factoryButton.push_back(factoryButton);
        }
        vector<string> soundPath = {"resources/button/button_sound.bmp", "resources/button/button_mute.bmp"};
        soundButton.LoadBitmapByString(soundPath,RGB(255,255,255));
        soundButton.SetTopLeft(0,0);
        SoundManager::mute = true;
        soundButton.SwitchMute();
        
    }

    void Map::ShowFactoryButton()
    {
        for (int i = 0; i < buttonNumber; i++)
        {
            _factoryButton[i].ShowBitmap(1.2);
            if (IsCursorInObj(_factoryButton[i]))
            {
                _factoryButton[i].TowerInfo.ShowBitmap();
            }
        }
        soundButton.ShowBitmap();
    }

    void Map::UpdateFactoryButton()
    {
        for (int i = 0; i < buttonNumber; i++)
        {
            _factoryButton[i].Update();
        }
    }

    int Map::HandleButtonClicked(int money)
    {
        for (int i = 0; i < buttonNumber; i++)
        {
            if (_factoryButton[i].IsCursorFocus() && priceTable[i] <= money)
            {
                _factoryButton[i].SetClicked(true);
                return priceTable[i];
            }
        }
        if (soundButton.IsCursorFocus() )
        {
            soundButton.SwitchMute();
        }
        return 0;
    }

    int Map::HandleShortCut(UINT uint,int money)
    {
        TowerType target ;
        switch (uint)
        {
        case 'Q':
            target = TowerType::dart;
            break;
        case 'W':
            target = TowerType::nail;
            break;
        case 'E':
            target = TowerType::ice;
            break;
        case 'R':
            target = TowerType::bomb;
            break;
        case 'A':
            target = TowerType::spikes;
            break;
        case 'S':
            target = TowerType::glue;
            break;
        case 'D':
            target = TowerType::boomerang;
            break;
        case 'F':
            target = TowerType::super;
            break;
        default:
            return 0;
        }
        if( priceTable[(int)target] <= money )
        {
            _factoryButton[(int)target].SetClicked(true);
            return priceTable[(int)target];
        }
        return 0;
    }

    GameObject Map::GetBackground()
    {
        return _background;
    }

    vector<vector<Vector2>> Map::_route = {{{100, 100}, {110, 110}, {0, 100}, {200, 200}}};

    vector<vector<Vector2>> Map::GetRoute()
    {
        return _route;
    }

    void Map::SetRoute(vector<vector<Vector2>> route)
    {
        _route = route;
    }

    bool Map::IsOverLapRoad(GameObject target)
    {
        for (int i = 0; i < static_cast<int>(_road.size()); i++)
        {
            if (Btd::IsOverlap(_road[i], target))
            {
                return true;
            }
        }
        return false;
    }

    bool Map::IsOverSidebar(GameObject target)
    {
        if (Btd::IsOverlap(_sidebar, target))
        {
            return true;
        }
        return false;
    }

    int Map::GetInitMoney()
    {
        return InitMoney;
    }

    int Map::GetInitLives()
    {
        return InitLives;
    }

    MapType Map::GetMapType()
    {
        return mapType;
    }

    void Map::SetMapType(MapType type)
    {
        mapType = type;
    }

    vector<int> Map::GetPriceTable()
    {
        return priceTable;
    }

    vector<vector<UnitRound>> Map::GetRounds()
    {
        return _rounds;
    }

    void Map::SetRounds(vector<vector<UnitRound>> round)
    {
        _rounds = round;
    }
}
