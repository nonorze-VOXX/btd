#include "stdafx.h"
#include "Spikes.h"

namespace Btd
{
    Spikes::Spikes()
    {
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
}
