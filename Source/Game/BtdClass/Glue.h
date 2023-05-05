#pragma once
#include "tower.h"

namespace Btd
{
    class Glue
    {
    public:
        Glue();
        void LoadBitmapByString(vector<string> filepaths, COLORREF color);
        void SetCenter(int x, int y);
        void SetIsMove(bool isMove);
        void SetActive(bool active);
        bool IsMovable();
        void ShowBitmap();
        bool IsCursorFocus();
        void SetClicked(bool clicked);
        void SetDamageType(DamageType::DamageType damageType);
        void DetectHitBalloon();
        void UpdateCantHitBloons();
        void Update();
        Vector2 GetCenter();
        
        Tower tower;
        Throwable throwable;
    private:
        int _range;
    };
}
