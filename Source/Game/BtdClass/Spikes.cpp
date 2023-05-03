#include "stdafx.h"
#include "Spikes.h"

namespace Btd
{
    Spikes::Spikes()
    {
        _throwable.SetMaxExistTime(-1);
        _throwable.SetPenetrate(true);
        _throwable.setCantHtBloonTime(0);
    }

    void Spikes::LoadBitmapByString(vector<string> filepaths, COLORREF color)
    {
        _tower.LoadBitmapByString(filepaths, color);
        _throwable.LoadBitmapByString(filepaths, color);
    }

    void Spikes::SetCenter(int x, int y)
    {
        _tower.SetCenter(x, y);
        _throwable.SetCenter(x, y);
    }

    void Spikes::SetFrameIndexOfBitmap(int frameIndex)
    {
        _tower.SetFrameIndexOfBitmap(frameIndex);
        _throwable.SetFrameIndexOfBitmap(frameIndex);
    }

    void Spikes::SetIsMove(bool isMove)
    {
        _tower.SetIsMove(isMove);
    }

    void Spikes::SetActive(bool active)
    {
        _tower.SetActive(active);
        _throwable.SetActive(active);
    }

    bool Spikes::IsMovable()
    {
        return _tower.IsMovable();
    }

    void Spikes::ShowBitmap()
    {
        _tower.ShowBitmap();
        _throwable.ShowBitmap();
    }

    bool Spikes::IsCursorFocus()
    {
        return _tower.IsCursorFocus();
    }

    void Spikes::SetClicked(bool clicked)
    {
        _tower.SetClicked(clicked);
    }

    void Spikes::SetDamageType(DamageType::DamageType damageType)
    {
        _throwable.SetDamageType(damageType);
    }

    void Spikes::DetectHitBalloon()
    {
        _throwable.DetectHitBalloon();
    }

    void Spikes::UpdateCantHitBloons()
    {
        _throwable.UpdateCantHitBloons();
    }

    void Spikes::Update()
    {
        if (_throwable.GetActive())
        {
            DetectHitBalloon();
            UpdateCantHitBloons();
        }
    }
}
