#ifndef CELLSIM_NUMERICS_VECTOR3T_HPP
#define CELLSIM_NUMERICS_VECTOR3T_HPP

#include "base.hpp"
#include <math.h>

namespace CellSim::Numerics
{
    /// @brief 3次元ベクトル型
    /// @tparam TNum 数値型
    template <NumberType TNum>
    struct Vector3T {
        public:

        [[nodiscard]] static constexpr Vector3T Zero() noexcept;

        TNum X;
        TNum Y;
        TNum Z;

        constexpr Vector3T() noexcept;
        explicit constexpr Vector3T(TNum x) noexcept;
        constexpr Vector3T(TNum x, TNum y) noexcept;
        constexpr Vector3T(TNum x, TNum y, TNum z) noexcept;

        constexpr Vector3T& operator+=(Vector3T right) noexcept;
        constexpr Vector3T& operator-=(Vector3T right) noexcept;
        constexpr Vector3T& operator*=(TNum right) noexcept;
        constexpr Vector3T& operator/=(TNum right) noexcept;

        [[nodiscard]] TNum Length() const noexcept;

        [[nodiscard]] Vector3T Normalize() const noexcept;

        [[nodiscard]] constexpr TNum SquareLength() const noexcept;
    };

    template <NumberType TNum>
    [[nodiscard]] constexpr bool operator==(Vector3T<TNum> left, Vector3T<TNum> right) noexcept;

    template <NumberType TNum>
    [[nodiscard]] constexpr bool operator!=(Vector3T<TNum> left, Vector3T<TNum> right) noexcept;

    template <NumberType TNum>
    [[nodiscard]] constexpr Vector3T<TNum> operator+(Vector3T<TNum> left, Vector3T<TNum> right) noexcept;

    template <NumberType TNum>
    [[nodiscard]] constexpr Vector3T<TNum> operator-(Vector3T<TNum> left, Vector3T<TNum> right) noexcept;

    template <NumberType TNum>
    [[nodiscard]] constexpr Vector3T<TNum> operator*(Vector3T<TNum> left, Vector3T<TNum> right) noexcept;

    template <NumberType TNum>
    [[nodiscard]] constexpr Vector3T<TNum> operator*(TNum left, Vector3T<TNum> right) noexcept;

    template <NumberType TNum>
    [[nodiscard]] constexpr Vector3T<TNum> operator*(Vector3T<TNum> left, TNum right) noexcept;

    template <NumberType TNum>
    [[nodiscard]] constexpr Vector3T<TNum> operator/(Vector3T<TNum> left, TNum right) noexcept;
}

namespace CellSim::Numerics
{
    template <NumberType TNum>
    constexpr Vector3T<TNum> Vector3T<TNum>::Zero() noexcept
    {
        return Vector3T<TNum>(0, 0, 0);
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum>::Vector3T() noexcept
        : X(0)
        , Y(0)
        , Z(0)
    {
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum>::Vector3T(TNum x) noexcept
        : X(x)
        , Y(0)
        , Z(0)
    {
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum>::Vector3T(TNum x, TNum y) noexcept
        : X(x)
        , Y(y)
        , Z(0)
    {
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum>::Vector3T(TNum x, TNum y, TNum z) noexcept
        : X(x)
        , Y(y)
        , Z(z)
    {
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum>& Vector3T<TNum>::operator+=(Vector3T right) noexcept
    {
        X += right.X;
        Y += right.Y;
        Z += right.Z;

        return *this;
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum>& Vector3T<TNum>::operator-=(Vector3T right) noexcept
    {
        X -= right.X;
        Y -= right.Y;
        Z -= right.Z;

        return *this;
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum>& Vector3T<TNum>::operator*=(TNum right) noexcept
    {
        X *= right;
        Y *= right;
        Z *= right;

        return *this;
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum>& Vector3T<TNum>::operator/=(TNum right) noexcept
    {
        X /= right;
        Y /= right;
        Z /= right;

        return *this;
    }

    template <NumberType TNum>
    inline TNum Vector3T<TNum>::Length() const noexcept
    {
        return ::sqrt(SquareLength());
    }

    template <NumberType TNum>
    inline Vector3T<TNum> Vector3T<TNum>::Normalize() const noexcept
    {
        TNum length = Length();
        if (Length() == 0.0) return Vector3T<TNum>();

        return *this / length;
    }

    template <NumberType TNum>
    constexpr TNum Vector3T<TNum>::SquareLength() const noexcept
    {
        return X * X + Y * Y + Z * Z;
    }

    template <NumberType TNum>
    constexpr bool operator==(Vector3T<TNum> left, Vector3T<TNum> right) noexcept
    {
        return left.X == right.X && left.Y == right.Y && left.Z == right.Z;
    }

    template <NumberType TNum>
    constexpr bool operator!=(Vector3T<TNum> left, Vector3T<TNum> right) noexcept
    {
        return !(left == right);
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum> operator+(Vector3T<TNum> left, Vector3T<TNum> right) noexcept
    {
        return Vector3T<TNum>(left.X + right.X, left.Y + right.Y, left.Z + right.Z);
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum> operator-(Vector3T<TNum> left, Vector3T<TNum> right) noexcept
    {
        return Vector3T<TNum>(left.X - right.X, left.Y - right.Y, left.Z - right.Z);
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum> operator*(Vector3T<TNum> left, Vector3T<TNum> right) noexcept
    {
        return Vector3T<TNum>(left.X * right.X, left.Y * right.Y, left.Z * right.Z);
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum> operator*(TNum left, Vector3T<TNum> right) noexcept
    {
        return Vector3T<TNum>(left * right.X, left * right.Y, left * right.Z);
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum> operator*(Vector3T<TNum> left, TNum right) noexcept
    {
        return Vector3T<TNum>(left.X * right, left.Y * right, left.Z * right);
    }

    template <NumberType TNum>
    constexpr Vector3T<TNum> operator/(Vector3T<TNum> left, TNum right) noexcept
    {
        return Vector3T<TNum>(left.X / right, left.Y / right, left.Z / right);
    }
}

#endif //!CELLSIM_NUMERICS_VECTOR3T_HPP