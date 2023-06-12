#pragma once
#include <functional>
#include <random>
#include <set>
#include "BtdUtil.h"
#include "../../Library/gameutil.h"
#include "../config.h"
#include "GameObject.h"
namespace Btd {
    const int 🍌💰 = 10;
    const int 🐼🎦delay = 200;
    const int 🐼🍌cooldown = 4000;
    constexpr float 🐼speed = (100.0f * (static_cast<float>(GAME_CYCLE_TIME) / 1000.0f));
    constexpr float 🍌speed = (300.0f * (static_cast<float>(GAME_CYCLE_TIME) / 1000.0f));
    constexpr float 🐵Maxspeed = (200.0f * (static_cast<float>(GAME_CYCLE_TIME) / 1000.0f));
    constexpr float 🐵Minspeed = (100.0f * (static_cast<float>(GAME_CYCLE_TIME) / 1000.0f));
    constexpr float 🐵Backspeed = (50.0f * (static_cast<float>(GAME_CYCLE_TIME) / 1000.0f)); // they are sad and slow
    class Cavallo : public GameObject
    {
    public:
        void Init();
        void Throw();
        void Move();
        void Move🐒🍌();
        void Draw();
        void DrawBanana();
        void Harder();
        void SetDest(Vector2);
        int OnClick();
        void Release();
        static bool CAVALLO;
        static float Multiplier;
        class Banana : public GameObject{
        public:
            void Load();
            void Init();
            void Move();
            void Draw();
            void SetDest(Vector2);
            bool IsAlive();
            bool GotCarry();
            void SetOwnerPos(int X, int Y);
            bool OnClick();
            void 💀();
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
        bool _isStuckX;
        bool _isStuckY;
        int _frameIndex;
        Vector2 _dest;
        Vector2 _smoothMoving;
        clock_t _lastThrowTime;
        clock_t _coolDown;
        clock_t _lastFrameTime;
        vector<Banana> _🍌s;
        Banana _base🍌;
    };
}

