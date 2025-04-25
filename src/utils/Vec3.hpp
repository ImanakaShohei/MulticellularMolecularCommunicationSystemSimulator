/**
 * @file Vec3.hpp
 * @author Takanori Saiki
 * @brief 3D Vector class
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cmath>
#include <iostream>
#include <random>

/**
 * @class Vec3
 * @brief 3次元のベクトルを扱うクラス。
 */
class Vec3
{
  public:
    constexpr Vec3() noexcept;
    constexpr Vec3(double x, double y, double z = 0) noexcept;

    Vec3 operator-() const noexcept;
    Vec3 operator+(Vec3 obj) const noexcept;
    Vec3 operator-(Vec3 obj) const noexcept;
    Vec3 &operator+=(const Vec3 &obj) noexcept;
    Vec3 &operator-=(const Vec3 &obj) noexcept;

    bool operator==(const Vec3 &obj) const noexcept;
    bool operator!=(const Vec3 &obj) const noexcept;

    Vec3 timesScalar(double num) const noexcept;          // スカラー倍
    double dot(Vec3 vec) const noexcept;                  // 内積
    Vec3 rotate(double theta, double phi) const noexcept; // theta, phi = Rad で回転
    Vec3 cross(Vec3 vec) const noexcept;                  // 外積
    Vec3 normalize() const noexcept;                      // 正規化
    double length() const noexcept;                       // 長さ
    constexpr double squareLength() const noexcept;       // ノルム
    double dist(Vec3 vec) const noexcept;                 // 距離

    void print() const noexcept;

    static Vec3 zero() noexcept;
    static Vec3 randomDirection2() noexcept; // 方向のみを表すランダムな正規化されたベクトル(z=0で固定)を返す。
    static Vec3 randomDirection3() noexcept; // 方向のみを表すランダムな正規化されたベクトルを返す。

    double x, y, z; //!< x, y, z座標
};

constexpr Vec3 operator*(Vec3 const& left, double right) noexcept
{
    return Vec3(left.x * right, left.y * right, left.z * right);
}

constexpr Vec3 operator*(Vec3&& left, double right) noexcept
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}

constexpr Vec3 operator*(double left, Vec3 const& right) noexcept
{
    return right * left;
}

constexpr Vec3 operator*(double left, Vec3&& right) noexcept
{
    return ::std::move(right) * left;
}

constexpr Vec3 operator/(Vec3 const& left, double right) noexcept
{
    return Vec3(left.x / right, left.y / right, left.z / right);
}

constexpr Vec3 operator/(Vec3&& left, double right) noexcept
{
    left.x /= right;
    left.y /= right;
    left.z /= right;

    return left;
}

/**
 * @brief 基本となるコンストラクタ。すべての成分を0に設定する。
 *
 */
constexpr Vec3::Vec3() noexcept : x(0), y(0), z(0) {}

/**
 * @brief x, y, z成分を指定して初期化するコンストラクタ。zはデフォルトで0。
 *
 * @param x
 * @param y
 * @param z (default: 0)
 */
constexpr Vec3::Vec3(double x, double y, double z) noexcept : x(x), y(y), z(z) {}

/**
 * @brief ベクトルを定数倍する。
 *
 * @param num
 * @return Vec3
 */
inline Vec3 Vec3::timesScalar(double num) const noexcept
{
    return Vec3(x * num, y * num, z * num);
}

/**
 * @brief ベクトルを正規化する。ただし、長さが0の場合は0ベクトルを返す。
 *
 * @return Vec3
 */
inline Vec3 Vec3::normalize() const noexcept
{
    double len = this->length();

    if (len == 0)
        return Vec3(0, 0, 0);

    return Vec3(x / len, y / len, z / len);
}

/**
 * @brief ベクトルの長さを返す。
 *
 * @return double
 */
inline double Vec3::length() const noexcept
{
    return std::sqrt(x * x + y * y + z * z);
}

/**
 * @brief ベクトルのノルムを返す。
 *
 * @return double
 */
constexpr double Vec3::squareLength() const noexcept
{
    return x * x + y * y + z * z;
}

/**
 * @brief ベクトル同士の距離を返す。
 *
 * @param vec
 * @return double
 */
inline double Vec3::dist(Vec3 vec) const noexcept
{
    Vec3 diff = *this - vec;

    return diff.length();
}