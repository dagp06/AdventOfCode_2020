#include "MathHelper.h"

namespace MathHelper
{
    Vector2 Vector2::operator+(const Vector2& _other) const
    {
        return Vector2(x + _other.x, y + _other.y);
    }

    Vector2 Vector2::operator-(const Vector2& _other) const
    {
        return Vector2(x - _other.x, y - _other.y);
    }

    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    Vector2 Vector2::operator*(int _mult) const
    {
        return Vector2(_mult * x, _mult * y);
    }

    Vector2& Vector2::operator+=(const Vector2& _other)
    {
        x += _other.x;
        y += _other.y;

        return *this;
    }

    Vector2 Vector2::DistanceTo(const Vector2& _other) const
    {
        return _other - *this;
    }

    int Vector2::ManathanDistanceTo(const Vector2& _other) const
    {
        Vector2 vect = DistanceTo(_other);
        return abs(vect.x) + abs(vect.y);
    }

    void Vector2::Rotate(int _angle)
    {
        float angleRad = _angle / 180.f * PI;

        float newX = (x * cos(angleRad) - y * sin(angleRad));
        float newY = (x * sin(angleRad) + y * cos(angleRad));
        x = round(newX);
        y = round(newY);
    }

    ostream& operator<<(ostream& _os, const Vector2& _vect)
    {
        _os << "(" << _vect.x << ", " << _vect.y << ")";
        return _os;
    }

    Vector2 operator*(int _mult, Vector2 _vect)
    {
        return _vect * _mult;
    }
}