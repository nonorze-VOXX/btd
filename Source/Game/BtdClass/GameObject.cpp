#include "stdafx.h"
#include "GameObject.h"


namespace Btd
{
    void GameObject::Update()
    {
    }

    void GameObject::SetActive(bool active)
    {
        _isActive = active;
    }

    bool GameObject::GetActive()
    {
        return _isActive;
    }

    void GameObject::SetTag(string tag)
    {
        _tag = tag;
    }

    string GameObject::GetTag()
    {
        return _tag;
    }

    Vector2 GameObject::GetCenter()
    {
        return {static_cast<float>(GetLeft()) + GetWidth() / 2, static_cast<float>(GetTop()) + GetHeight() / 2};
    }


    void GameObject::SetCenter(int x, int y)
    {
        SetTopLeft(x - GetWidth() / 2, y - GetHeight() / 2);
    }

    void GameObject::SetBottomCenter(int x, int y)
    {
        SetTopLeft(x - GetWidth() / 2, y - GetHeight());
    }

    Vector2 GameObject::GetBottomCenter()
    {
        return {static_cast<float>(GetLeft()) +(float) GetWidth() / 2, static_cast<float>(GetTop()) +(float) GetHeight()};
    }


    bool GameObject::IsCursorFocus()
    {
        GameObject mouse;
        mouse.LoadEmptyBitmap(1,1);
        mouse.SetTopLeft(GetCursorPosX(),GetCursorPosY());
        mouse.SetCollider({1,1});
        return Btd::IsOverlap(mouse,*this);
        if (GetLeft() < GetCursorPosX() && GetCursorPosX() < GetLeft() + GetWidth() &&
            GetTop() < GetCursorPosY() && GetCursorPosY() < GetTop() + GetHeight())
        {
            return true;
        }
        return false;
    }

    void GameObject::SetClicked(bool clicked)
    {
        _isClicked = clicked;
    }

    void GameObject::SetHeight(int height)
    {
        int bias = height - GetHeight();
        locations[frameIndex].bottom += bias;
    }

    void GameObject::SetWidth(int width)
    {
        int bias = width - GetWidth();
        locations[frameIndex].right += bias;
    }

    void GameObject::SetCollider(Vector2 r)
    {
        Collider = r;
    }

    Vector2 GameObject::GetCollider()
    {
        
        return (Collider.X==0.F)?Vector2{static_cast<float>(GetWidth()),static_cast<float>(GetHeight())}:Collider;
    }

    bool IsOverlap(GameObject& character, GameObject& other)
    {
        auto delta =Vector2Sub( character.GetCenter(),other.GetCenter());
        auto charaCollider = character.GetCollider();
        auto otherCollider = other.GetCollider();
        Vector2 colliderDistance = {
            (charaCollider.X + otherCollider.X) / 2.F,
            (charaCollider.Y + otherCollider.Y) / 2.F
        };
        return (abs(delta.X)<colliderDistance.X&&abs(delta.Y)<colliderDistance.Y); 
    }

    bool IsCursorInObj(GameObject obj)
    {
        if (obj.GetLeft() <= GetCursorPosX() && GetCursorPosX() <= obj.GetLeft() + obj.GetWidth() &&
            obj.GetTop() <= GetCursorPosY() && GetCursorPosY() <= obj.GetTop() + obj.GetHeight())
        {
            return true;
        }
        return false;
    }
}
