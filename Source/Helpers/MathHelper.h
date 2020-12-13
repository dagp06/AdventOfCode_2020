#pragma once
#include "../CommonDefinitions.h"

#include <iostream>

using namespace std;

namespace MathHelper
{
    const double PI = acos(-1);

    class Vector2
    {
    public:
        Vector2() : x(0), y(0) {};
        Vector2(int _val) : x(_val), y(_val) {};
        Vector2(int _x, int _y) : x(_x), y(_y) {};

        Vector2 operator+(const Vector2& _other) const;
        Vector2 operator-(const Vector2& _other) const;
        Vector2 operator-() const;
        Vector2 operator*(int _mult) const;

        Vector2& operator+=(const Vector2& _other);

        friend ostream& operator<<(ostream& _os, const Vector2& _vect);

        Vector2 DistanceTo(const Vector2& _other) const;
        int     ManathanDistanceTo(const Vector2& _other) const;

        void    Rotate(int _angle);

    private:
        int x;
        int y;
    };

    Vector2 operator*(int _mult, Vector2 _vect);
};
