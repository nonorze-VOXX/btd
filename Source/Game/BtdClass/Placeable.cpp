#include "stdafx.h"
#include "Placeable.h"

namespace Btd
{

    void Placeable::LoadBitmapByString(vector<string> filepaths, COLORREF color)
    {
        tower.LoadBitmapByString(filepaths, color);
        throwable.LoadBitmapByString(filepaths, color);
    }

    void Placeable::SetCenter(int x, int y)
    {
        tower.SetCenter(x, y);
        throwable.SetCenter(x, y);
    }

    void Placeable::SetIsMove(bool isMove)
    {
        tower.SetIsMove(isMove);
    }

    void Placeable::SetActive(bool active)
    {
        tower.SetActive(active);
        throwable.SetActive(active);
    }

    bool Placeable::IsMovable()
    {
        return tower.IsMovable();
    }

    void Placeable::ShowBitmap()
    {
        tower.ShowBitmap();
        throwable.ShowBitmap();
        if (tower.IsMovable())
        {
            tower.RangeCircle.ShowBitmap(static_cast<float>(_range) / 100.0);
        }
    }

    bool Placeable::IsCursorFocus()
    {
        return tower.IsCursorFocus();
    }

    void Placeable::SetClicked(bool clicked)
    {
        tower.SetClicked(clicked);
    }

    void Placeable::SetDamageType(DamageType::DamageType damageType)
    {
        throwable.SetDamageType(damageType);
    }

    void Placeable::DetectHitBalloon()
    {
        throwable.DetectHitBalloon();
    }

    void Placeable::UpdateCantHitBloons()
    {
        throwable.UpdateCantHitBloons();
    }

    void Placeable::Update()
    {
        if (throwable.GetActive())
        {
            DetectHitBalloon();
            UpdateCantHitBloons();
        }
        tower.RangeCircle.SetCenter(static_cast<int>(GetCenter().X) - (_range - 100),
                              static_cast<int>(GetCenter().Y) - (_range - 100));
    }

    Vector2 Placeable::GetCenter()
    {
        return tower.GetCenter();
    }
}
