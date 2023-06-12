#pragma once
#include "GameObject.h"
#include "BtdUtil.h"
#include <list>
#include <map>

namespace Btd
{
    class Bloon : public GameObject
    {
    private:
        int nowRouteTarget = 0;
        float _speed = 3;
        int _layer = 0;
        bool _isPoped = false;
        bool _isGoaled = false;
        BloonType::BloonType type = BloonType::normal;
        int _freezeTime;
        float _slowerSpeed;
        float _originSpeed;
        int route = 0;
        bool _isFreeze;
        GameObject _frost;
        int _explodeTime;
        bool _isExplode;
        int _id = 0;  // bloon unique id

    public:
        int GetExplodeTime() const;
        void SetExplodeTime(int explodeTime);

        Bloon();;

        Bloon(int layer);

        static bool resistDamegeMap[5][5];

        void SetNowRouteTarget(int target);

        void Setspeed(float speed);

        void SetType(BloonType::BloonType t);

        void Update() override;
        void SetRoute(int n);
        int Getroute();
        float GetSpeed();
        BloonType::BloonType GetType();

        void Move(vector<Vector2> route);

        void Pop(int damage, DamageType damageType);

        int GetNowRouteTarget();

        bool IsPoped();
        bool IsGoaled();
        void SetIsPoped(bool poped);
        void SetIsGoaled(bool goaled);
        void SetLayer(int layer);
        void FreezeInPeriod(int time);
        int GetLayer();
        void BloonShow();
        void ShowExplode();
        bool IsExplode();
        void Init();
        void SetId(int id);
        int GetId();
    };
}
