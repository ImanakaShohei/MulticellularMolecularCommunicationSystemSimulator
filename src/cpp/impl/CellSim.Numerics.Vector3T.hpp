#ifndef CELLSIM_NUMERICS_VECTOR3T_HPP
#define CELLSIM_NUMERICS_VECTOR3T_HPP

#include "base.hpp"
#include <math.h>

namespace CellSim::Numerics
{
    /// @brief 3次元ベクトル型
    /// @tparam TFloat 数値型
    template <::std::floating_point TFloat>
    struct Vector3T {
        public:

        [[nodiscard]] static constexpr Vector3T Zero() noexcept;

        TFloat X;
        TFloat Y;
        TFloat Z;

        constexpr Vector3T() noexcept;
        explicit constexpr Vector3T(TFloat x) noexcept;
        constexpr Vector3T(TFloat x, TFloat y) noexcept;
        constexpr Vector3T(TFloat x, TFloat y, TFloat z) noexcept;

        constexpr Vector3T& operator+=(Vector3T right) noexcept;
        constexpr Vector3T& operator-=(Vector3T right) noexcept;

        [[nodiscard]] TFloat Length() const noexcept;

        [[nodiscard]] Vector3T Normalize() const noexcept;

        [[nodiscard]] constexpr TFloat SquareLength() const noexcept;
    };

    template <::std::floating_point TFloat>
    [[nodiscard]] constexpr Vector3T<TFloat> operator+(Vector3T<TFloat> left, Vector3T<TFloat> right) noexcept;

    template <::std::floating_point TFloat>
    [[nodiscard]] constexpr Vector3T<TFloat> operator-(Vector3T<TFloat> left, Vector3T<TFloat> right) noexcept;

    template <::std::floating_point TFloat>
    [[nodiscard]] constexpr Vector3T<TFloat> operator*(Vector3T<TFloat> left, Vector3T<TFloat> right) noexcept;

    template <::std::floating_point TFloat>
    [[nodiscard]] constexpr Vector3T<TFloat> operator*(TFloat left, Vector3T<TFloat> right) noexcept;

    template <::std::floating_point TFloat>
    [[nodiscard]] constexpr Vector3T<TFloat> operator*(Vector3T<TFloat> left, TFloat right) noexcept;

    template <::std::floating_point TFloat>
    [[nodiscard]] constexpr Vector3T<TFloat> operator/(Vector3T<TFloat> left, TFloat right) noexcept;
}

namespace CellSim::Numerics
{
    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat> Vector3T<TFloat>::Zero() noexcept
    {
        return Vector3T<TFloat>(0, 0, 0);
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat>::Vector3T() noexcept
        : X(0)
        , Y(0)
        , Z(0)
    {
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat>::Vector3T(TFloat x) noexcept
        : X(x)
        , Y(0)
        , Z(0)
    {
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat>::Vector3T(TFloat x, TFloat y) noexcept
        : X(x)
        , Y(y)
        , Z(0)
    {
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat>::Vector3T(TFloat x, TFloat y, TFloat z) noexcept
        : X(x)
        , Y(y)
        , Z(z)
    {
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat>& Vector3T<TFloat>::operator+=(Vector3T right) noexcept
    {
        X += right.X;
        Y += right.Y;
        Z += right.Z;
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat>& Vector3T<TFloat>::operator-=(Vector3T right) noexcept
    {
        X -= right.X;
        Y -= right.Y;
        Z -= right.Z;
    }

    template <::std::floating_point TFloat>
    inline TFloat Vector3T<TFloat>::Length() const noexcept
    {
        return ::sqrt(SquareLength());
    }

    template <::std::floating_point TFloat>
    inline Vector3T<TFloat> Vector3T<TFloat>::Normalize() const noexcept
    {
        TFloat length = Length();
        if (Length() == 0.0) return Vector3T<TFloat>();

        return *this / length;
    }

    template <::std::floating_point TFloat>
    constexpr TFloat Vector3T<TFloat>::SquareLength() const noexcept
    {
        return X * X + Y * Y + Z * Z;
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat> operator+(Vector3T<TFloat> left, Vector3T<TFloat> right) noexcept
    {
        return Vector3T<TFloat>(left.X + right.X, left.Y + right.Y, left.Z + right.Z);
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat> operator-(Vector3T<TFloat> left, Vector3T<TFloat> right) noexcept
    {
        return Vector3T<TFloat>(left.X - right.X, left.Y - right.Y, left.Z - right.Z);
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat> operator*(Vector3T<TFloat> left, Vector3T<TFloat> right) noexcept
    {
        return Vector3T<TFloat>(left.X * right.X, left.Y * right.Y, left.Z * right.Z);
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat> operator*(TFloat left, Vector3T<TFloat> right) noexcept
    {
        return Vector3T<TFloat>(left * right.X, left * right.Y, left * right.Z);
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat> operator*(Vector3T<TFloat> left, TFloat right) noexcept
    {
        return Vector3T<TFloat>(left.X * right, left.Y * right, left.Z * right);
    }

    template <::std::floating_point TFloat>
    constexpr Vector3T<TFloat> operator/(Vector3T<TFloat> left, TFloat right) noexcept
    {
        return Vector3T<TFloat>(left.X / right, left.Y / right, left.Z / right);
    }
}

#endif //!CELLSIM_NUMERICS_VECTOR3T_HPP