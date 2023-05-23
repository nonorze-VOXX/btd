#pragma once
#include <vector>

#include "BtdUtil.h"
#include "Tower.h"

namespace Btd
{
    
    class Placeable
    {
        public:
            Placeable()=default;
            void LoadBitmapByString(std::vector<std::string> filepaths, COLORREF color);
            void SetCenter(int x, int y);
            void SetIsMove(bool isMove);
            void SetActive(bool active);
            bool IsMovable();
            void ShowBitmap();
            bool IsCursorFocus();
            void SetClicked(bool clicked);
            void SetDamageType(DamageType damageType);
            void DetectHitBalloon();
            void UpdateCantHitBloons();
            void Update();
            Vector2 GetCenter();
            
            Tower tower;
            Throwable throwable;
        protected:
            int _range=25;
        
    };
}
