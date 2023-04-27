#pragma once
#include "BtdUtil.h"
#include "../../Library/gameutil.h"

namespace Btd
{
    class GameObject : public game_framework::CMovingBitmap
    {
    protected:
        bool _isActive = true;
        string _tag = "default";
        int deltaTime = 10;
        bool _isClicked;
        Vector2 Collider={0,0};

    public:
        virtual ~GameObject() = default;
        virtual void Update();
        void SetActive(bool active);
        bool GetActive();
        void SetTag(string tag);
        string GetTag();
        Vector2 GetCenter();
        void SetCenter(int x, int y);
        void SetBottomCenter(int x, int y);
        Vector2 GetBottomCenter();
        bool IsCursorFocus();
        void SetClicked(bool clicked);
        void SetHeight(int height);
        void SetWidth(int width);
        void SetCollider(Vector2);
        Vector2 GetCollider();
    };

    bool IsOverlap(GameObject& character, GameObject& other);
    bool IsCursorInObj(GameObject target);
}
