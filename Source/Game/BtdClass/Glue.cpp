#include "stdafx.h"
#include "Glue.h"

namespace Btd
{
    Glue::Glue()
    {
        _range = 35;
    }

    void Glue::LoadBitmapByString(vector<string> filepaths, COLORREF color)
    {
        tower.LoadBitmapByString(filepaths, color);
        throwable.LoadBitmapByString(filepaths, color);
    }
    void Glue::SetCenter(int x, int y)
    {
        tower.SetCenter(x, y);
        throwable.SetCenter(x, y);
    }

    void Glue::SetIsMove(bool isMove)
    {
        tower.SetIsMove(isMove);
    }

    void Glue::SetActive(bool active)
    {
        tower.SetActive(active);
        throwable.SetActive(active);
    }

    bool Glue::IsMovable()
    {
        return tower.IsMovable();
    }

    void Glue::ShowBitmap()
    {
        tower.ShowBitmap();
        throwable.ShowBitmap();
        if (tower.IsMovable())
        {
            tower.RangeCircle.ShowBitmap(static_cast<float>(_range) / 100.0);
        }
    }

    bool Glue::IsCursorFocus()
    {
        return tower.IsCursorFocus();
    }

    void Glue::SetClicked(bool clicked)
    {
        tower.SetClicked(clicked);
    }

    void Glue::SetDamageType(DamageType::DamageType damageType)
    {
        throwable.SetDamageType(damageType);
    }

    void Glue::DetectHitBalloon()
    {
        throwable.DetectHitBalloon();
    }

    void Glue::UpdateCantHitBloons()
    {
        throwable.UpdateCantHitBloons();
    }

    void Glue::Update()
    {
        if (throwable.GetActive())
        {
            DetectHitBalloon();
            UpdateCantHitBloons();
        }
        tower.RangeCircle.SetCenter(static_cast<int>(GetCenter().X) - (_range - 100),
                              static_cast<int>(GetCenter().Y) - (_range - 100));
    }

    Vector2 Glue::GetCenter()
    {
        return tower.GetCenter();
    }
}
