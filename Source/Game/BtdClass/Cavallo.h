#pragma once
#include <functional>
#include "BtdUtil.h"
#include "../../Library/gameutil.h"
#include "GameObject.h"
namespace Btd {
    class Cavallo :
        public GameObject
    {
    public:
        void Init();
        void Throw();
        void Move();
        void Draw();
        void SetDest(Vector2);

    private:
        class 🍌 : GameObject{
            void Load();
            void Init();
            void Move();
            void Draw();
        };
        function<void()> Eat🍌;
        Vector2 _dest;
        clock_t _lastThrowTime;
        clock_t _coolDown;
        vector<🍌> _bananas;
        🍌 _baseBanana;
    };
}

