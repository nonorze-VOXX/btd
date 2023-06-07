#pragma once
#include <functional>
#include <random>
#include <set>
#include "BtdUtil.h"
#include "../../Library/gameutil.h"
#include "../config.h"
#include "GameObject.h"
const int 🐼🎦delay = 200;
constexpr float 🐼speed = (100.0f * (static_cast<float>(GAME_CYCLE_TIME) / 1000.0));
constexpr float 🍌speed = (300.0f * (static_cast<float>(GAME_CYCLE_TIME) / 1000.0));
namespace Btd {
    class Cavallo : public GameObject
    {
    public:
        void Init(function<void()> 🍴🍌);
        void Throw();
        void Move();
        void Draw();
        void SetDest(Vector2);
        function<void()> Eat🍌;
        class Banana : public GameObject{
        public:
            void Load();
            void Init();
            void Move();
            void Draw();
            void SetDest(Vector2);
            bool IsAlive();
            void SetOwnerPos(int X, int Y);
        private:
            int 🐵X;
            int 🐵Y;
            clock_t _lastMoveTime;
            Vector2 _dest;
            bool _isAlive;
            bool _gotCarry;
            bool _isFlying;
        };
    private:
        float _GetRandomFloat(float lower = 48.0f, float upper = 763.0f);
        bool _isMirror;
        int _frameIndex;
        vector<function<bool()>> _actions;
        Vector2 _dest;
        Vector2 _smoothMoving;
        clock_t _lastThrowTime;
        clock_t _coolDown;
        clock_t _lastFrameTime;
        vector<Banana> _🍌s;
        Banana _base🍌;

    };
}

