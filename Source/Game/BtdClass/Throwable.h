#pragma once
#include "GameObject.h"
#include "BtdUtil.h"
#include "Bloon.h"

namespace Btd
{
    class Throwable : public GameObject
    {
    protected:
        Vector2 _moveDirection;
        Vector2 _position = {0, 0};
        float _speed = 0;
        float _existTime = 0;
        float _maxExistTime = -1; // every throwable except bomb maxExistTime is -1 (because no use)
        int _damage = 1;
        int _maxPop = 0;
        int _poped = 0;
        int _cantHitBloonTime = 0;
        DamageType _damageType = DamageType::Normal;
        // throwable can't hit same balloon in one second
        vector<pair<int, int>> cantHitBloons = {};

    public:
        Throwable();
        void SetMaxPop(int i);
        Vector2 GetMoveDirection() const;

        void Update() override;
        void SetMaxExistTime(float);
        void InitByCenter(Vector2 position);

        void SetDamageType(DamageType damageType);;

        virtual void Move();

        void SetSpeed(float speed);

        float GetSpeed();

        void SetMoveDirection(float x, float y);

        virtual void DetectHitBalloon();

        void UpdateCantHitBloons();

        void SetCantHtBloonTime(int time);

        void SetDamage(int damage);
    };
}
