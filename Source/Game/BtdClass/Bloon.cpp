#include "stdafx.h"
#include "BtdUtil.h"
#include "Bloon.h"

#include "map.h"
#include "../../Library/audio.h"


namespace Btd
{
    //[bloontype][damagetype]
    //      normal boom ice
    //normal
    //black
    //white
    //rainbow
    //lead
    bool Bloon::resistDamegeMap[5][3] = {
        {true, true, true},
        {true, false, true},
        {true, true, false},
        {true, true, true},
        {false, true, false},
    };

    int Bloon::GetExplodeTime() const
    {
        return _explodeTime;
    }

    void Bloon::SetExplodeTime(int explodeTime)
    {
        _explodeTime = explodeTime;
    }

    void Bloon::SetNowRouteTarget(int target)
    {
        nowRouteTarget = target;
    }

    void Bloon::Setspeed(float speed)
    {
        _speed = speed;
        _originSpeed = speed;
    }

    void Bloon::Update()
    {
        if (_slowerTime > 0)
        {
            _slowerTime -= deltaTime;
            _speed = _slowerSpeed;
        }
        else
        {
            _speed = _originSpeed;
            _isFreeze = false;
        }
        if (GetActive())
        {
            Move(Map::GetRoute()[route]);
        }
        if (_isExplode)
        {
            ShowExplode();
        }
    }

    void Bloon::SetRoute(int n)
    {
        route = n;
    }

    int Bloon::Getroute()
    {
        return route;
    }

    float Bloon::GetSpeed()
    {
        return _speed;
    }

    void Bloon::Move(vector<Vector2> route)
    {
        Vector2 nowLocal = GetBottomCenter();
        Vector2 target = route[nowRouteTarget];
        Vector2 deltaMove = Vector2Sub(target, nowLocal);
        Vector2 moveDirection = Normailize(deltaMove);
        float speed = GetSpeed();
        deltaMove = {moveDirection.X * speed, moveDirection.Y * speed};

        int x = static_cast<int>(nowLocal.X) + static_cast<int>(deltaMove.X);
        int y = static_cast<int>(nowLocal.Y) + static_cast<int>(deltaMove.Y);
        if (Vector2Distance({static_cast<float>(x), static_cast<float>(y)}, target) < speed * 2 / 3)
        {
            x = static_cast<int>(target.X);
            y = static_cast<int>(target.Y);
            if (nowRouteTarget != static_cast<int>(route.size()) - 1)
                nowRouteTarget++;
            else
            {
                SetActive(false);
                _isGoaled = true;
            }
        }
        SetBottomCenter(x, y);
    }

    BloonType::BloonType Bloon::GetType()
    {
        return type;
    }

    void Bloon::Pop(int damage, DamageType::DamageType damageType)
    {
        if (resistDamegeMap[type][damageType] &&
            !(_isFreeze && damageType == DamageType::Normal)) // freeze bloon resist normal dmg
        {
            if (damageType == DamageType::Ice)
            {
                // if damageType == ice, damage = slowerTime
                SlowerInPeriod(_speed, damage);
                _isFreeze = true;
            }
            else
            {
                game_framework::CAudio *audio = game_framework::CAudio::Instance();
                audio->Play((int)BtdSound::POP,false);
                
                _layer -= damage;
                _explodeTime = 30;
                _isExplode = true;
                if (_layer >= 0)
                {
                    Setspeed(static_cast<float>(0.5 * _layer * _layer + _layer + 3));
                }
            }
        }else if(type == BloonType::lead)
        {
            game_framework::CAudio *audio = game_framework::CAudio::Instance();
            audio->Play((int)BtdSound::LEAD,false);
        }
    }

    bool Bloon::IsPoped()
    {
        return _isPoped;
    }

    void Bloon::SetIsPoped(bool poped)
    {
        _isPoped = poped;
    }

    void Bloon::SetIsGoaled(bool goaled)
    {
        _isGoaled = goaled;
    }

    void Bloon::SetLayer(int layer)
    {
        _layer = layer;
    }

    void Bloon::SlowerInPeriod(float subSpeed, int time)
    {
        _slowerSpeed = _speed - subSpeed;
        _slowerTime = time;
    }

    bool Bloon::IsGoaled()
    {
        return _isGoaled;
    }

    int Bloon::GetLayer()
    {
        return _layer;
    }

    void Bloon::BloonShow()
    {
        ShowBitmap();
        if (_isFreeze)
        {
            // _frost.SetCenter(static_cast<int>(GetCenter().X), static_cast<int>(GetCenter().Y));
            //_frost.SetTopLeft(GetLeft(), GetTop());
            //_frost.ShowBitmap();
        }
    }

    void Bloon::ShowExplode()
    {
        if (_explodeTime != 0)
        {
            SetFrameIndexOfBitmap(8);
            SetExplodeTime(_explodeTime - deltaTime);
        }
        else
        {
            _isExplode = false;
            if (_layer < 0)
            {
                _isPoped = true;
                return;
            }
            SetFrameIndexOfBitmap(_layer);
        }
    }

    bool Bloon::IsExplode()
    {
        return _isExplode;
    }

    void Bloon::Init()
    {
        _layer = 0;
        _isPoped = false;
        _slowerTime = 0;
        _isFreeze = false;
        _frost.LoadBitmapByString({"resources/bloon/frost.bmp"}, RGB(0, 0, 0));
        _explodeTime = 20;
        _isExplode = false;
    }
}
