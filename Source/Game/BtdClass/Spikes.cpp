#include "stdafx.h"
#include "Spikes.h"

namespace Btd
{
    Spikes::Spikes()
    {
        throwable.SetMaxExistTime(-1);
        throwable.SetCantHtBloonTime(0);
        throwable.SetMaxPop(10);
        throwable.SetDamageType(DamageType::Normal);
        _range = 25;
    }

    void Spikes::LoadBitmapByString(vector<string> filepaths, COLORREF color)
    {
        tower.LoadBitmapByString(filepaths, color);
        throwable.LoadBitmapByString(filepaths, color);
    }

    void Spikes::SetCenter(int x, int y)
    {
        tower.SetCenter(x, y);
        throwable.SetCenter(x, y);
    }

    void Spikes::SetFrameIndexOfBitmap(int frameIndex)
    {
        tower.SetFrameIndexOfBitmap(frameIndex);
        throwable.SetFrameIndexOfBitmap(frameIndex);
    }

    void Spikes::SetIsMove(bool isMove)
    {
        tower.SetIsMove(isMove);
    }

    void Spikes::SetActive(bool active)
    {
        tower.SetActive(active);
        throwable.SetActive(active);
    }

    bool Spikes::IsMovable()
    {
        return tower.IsMovable();
    }

    void Spikes::ShowBitmap()
    {
        tower.ShowBitmap();
        throwable.ShowBitmap();
        if (tower.IsMovable())
        {
            tower.RangeCircle.ShowBitmap(static_cast<float>(_range) / 100.0);
        }
    }

    bool Spikes::IsCursorFocus()
    {
        return tower.IsCursorFocus();
    }

    void Spikes::SetClicked(bool clicked)
    {
        tower.SetClicked(clicked);
    }

    void Spikes::SetDamageType(DamageType::DamageType damageType)
    {
        throwable.SetDamageType(damageType);
    }

    void Spikes::DetectHitBalloon()
    {
        throwable.DetectHitBalloon();
    }

    void Spikes::UpdateCantHitBloons()
    {
        throwable.UpdateCantHitBloons();
    }

    void Spikes::Update()
    {
        if (throwable.GetActive())
        {
            DetectHitBalloon();
            UpdateCantHitBloons();
        }
        tower.RangeCircle.SetCenter(static_cast<int>(GetCenter().X) - (_range - 100),
                              static_cast<int>(GetCenter().Y) - (_range - 100));
    }

    Vector2 Spikes::GetCenter()
    {
        return tower.GetCenter();
    }
}
