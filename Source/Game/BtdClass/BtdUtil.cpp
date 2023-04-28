#include "stdafx.h"
#include "BtdUtil.h"

#include <complex>
#include <valarray>

#define M_PI 3.1415926

namespace Btd
{
    Vector2 Spin90(const Vector2 a)
    {
        return {-a.Y, a.X};
    }

    Vector2 Spin45(const Vector2 a)
    {
        Vector2 b = Spin90(a);
        Vector2 c = Vector2Add(a, b);
        return Normailize(c.X / 2, c.Y / 2);
    }

    Vector2 Normailize(float x, float y)
    {
        float powSum = sqrt(x * x + y * y);
        return {x / powSum, y / powSum};
    }

    Vector2 Normailize(Vector2 v)
    {
        float powSum = sqrt(v.X * v.X + v.Y * v.Y);
        return {v.X / powSum, v.Y / powSum};
    }

    bool CompareVector2(Vector2 a, Vector2 b)
    {
        return a.X == b.X && a.Y == b.Y;
    }

    Vector2 Vector2Add(Vector2 a, Vector2 b)
    {
        return {a.X + b.X, a.Y + b.Y};
    }

    Vector2 Vector2Sub(Vector2 a, Vector2 b)
    {
        return {a.X - b.X, a.Y - b.Y};
    }

    Vector2 Vector2MulFloat(Vector2 a, float n)
    {
        return {a.X * n, a.Y * n};
    }

    float Vector2Distance(Vector2 a, Vector2 b)
    {
        float x = a.X - b.X;
        float y = a.Y - b.Y;
        return sqrt(x * x + y * y);
    }

    int GetCursorPosX()
    {
        POINT p;
        GetCursorPos(&p);
        HWND hwnd = FindWindowA(nullptr, "Game");
        ScreenToClient(hwnd, &p);
        return static_cast<int>(p.x);
    }

    int GetCursorPosY()
    {
        POINT p;
        GetCursorPos(&p);
        HWND hwnd = FindWindowA(nullptr, "Game");
        ScreenToClient(hwnd, &p);
        return static_cast<int>(p.y);
    }

    int GetFrameIndexByVector2(Vector2 dir)
    {
        /*
         * game object need 8 different directions frames
         * this function will return a proper frame index that game object need to show
         */
        double angleInRadians = std::atan2(dir.Y, dir.X);
        double angleInDegrees = (angleInRadians / M_PI) * 180.0;
        int index = 0;
        double tmp = 0;
        if (angleInDegrees < 0) angleInDegrees += 360;
        // angle:
        // up:   180 <-- 270 --> 359
        // down: 180 <--  90 --> 0
        tmp = (angleInDegrees + 25) / 45;
        return static_cast<int>(std::floor(tmp)) % 8;
    }

    Vector2 BezierCurve4Point(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float n)
    {
        auto tmp = Vector2Add(
            Vector2MulFloat(a, pow(n, 0) * pow(1 - n, 3)),
            Vector2MulFloat(b, pow(n, 1) * pow(1 - n, 2) * 3)
        );
        auto tmp1 = Vector2Add(
            Vector2MulFloat(c, pow(n, 2) * pow(1 - n, 1) * 3),
            Vector2MulFloat(d, pow(n, 3) * pow(1 - n, 0))
        );
        return Vector2Add(tmp, tmp1);
    }

    Vector2 BezierCurve4Point(vector<Vector2> points, float n)
    {
        return BezierCurve4Point(points[0], points[1], points[2], points[3], n);
    }

    Vector2 Spin(Vector2 v, float angle)
    {
        return {
            cos(angle) * v.X - sin(angle) * v.Y,
            sin(angle) * v.X + cos(angle) * v.Y
        };
    }
    Vector2 Scale(Vector2 v, float scale)
    {
        return {
            v.X*scale,
            v.Y*scale
        };
    }
    
}
