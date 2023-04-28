#ifndef TOWER_H
#define TOWER_H

#include "../../Library/gameutil.h"
#include "GameObject.h"
#include "Throwable.h"
#include <queue>
#include <string>
#include "Bloon.h"
#include "Button.h"

namespace Btd
{
    class Tower : public GameObject
    {
    public:
        Tower();
        ~Tower() override = default;
        Tower(Tower&&) = default;
        void Update() override;
        bool IsMovable();
        void SetIsMove(bool move);
        Vector2 getLocation();
        int GetRange();
        void SetThrowablePath(vector<string> name);
        vector<string> ThrowablePath;
        vector<shared_ptr<Throwable>> throwables;


        void SetThrowableLocal(Vector2 local);

        virtual void TowerShow();

        float GetShootDeltaTime();
        void SetShootDeltaTime(float time);
        virtual void Shoot(Vector2 target);
        virtual void PushThrowablePool();
        void UpdateThrowable();
        float GetShootTimeCounter();
        void SetShootTimeCounter(float);
        void Init();
        GameObject RangeCircle;
        Button UpgradeBtn[2];
        bool IsUpgrade[2];
        virtual void Upgrade(int level);
        int UpgradePrice[2] = {0, 0};
        void HandleUpgradeBtnFrame (int money);

    protected:
        bool _isMovable;
        // int _speed;
        int _range;
        int _buyMoney;
        int _sellMoney;
        Vector2 _location;
        GameObject throwableFactory;
        queue<shared_ptr<Throwable>> throwablePool;
        float shootDeltaTime;
        float shootTimecounter;
        Vector2 throwLocal;
        Bloon focus();
    };
}
#endif
