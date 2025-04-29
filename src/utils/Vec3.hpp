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

    constexpr Vec3 operator-() const noexcept;
    constexpr Vec3 &operator+=(const Vec3 &obj) noexcept;
    constexpr Vec3 &operator-=(const Vec3 &obj) noexcept;

    constexpr Vec3 timesScalar(double num) const noexcept;                      // スカラー倍
    static constexpr double dot(Vec3 const& left, Vec3 const& right) noexcept;  // 内積
    Vec3 rotate(double theta, double phi) const noexcept;                       // theta, phi = Rad で回転
    constexpr Vec3 cross(Vec3 vec) const noexcept;                              // 外積
    Vec3 normalize() const noexcept;                                            // 正規化
    double length() const noexcept;                                             // 長さ
    constexpr double squareLength() const noexcept;                             // ノルム
    double dist(Vec3 const& vec) const noexcept;                                // 距離

    void print() const noexcept;

    static constexpr Vec3 zero() noexcept;

    static Vec3 randomDirection2() noexcept; // 方向のみを表すランダムな正規化されたベクトル(z=0で固定)を返す。

    static Vec3 randomDirection3() noexcept; // 方向のみを表すランダムな正規化されたベクトルを返す。

    double x, y, z; //!< x, y, z座標
};

constexpr bool operator==(Vec3 const& left, Vec3 const& right) noexcept
{
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

constexpr bool operator!=(Vec3 const& left, Vec3 const& right) noexcept
{
    return left.x != right.x && left.y != right.y && left.z != right.z;
}

constexpr Vec3 operator+(Vec3 const& left, Vec3 const& right) noexcept
{
    return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
}

constexpr Vec3 operator+(Vec3&& left, Vec3 const& right) noexcept
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}

constexpr Vec3 operator+(Vec3 const& left, Vec3&& right) noexcept
{
    return ::std::move(right) + left;
}

constexpr Vec3 operator+(Vec3&& left, Vec3&& right) noexcept
{
    return ::std::move(left) + right;
}

constexpr Vec3 operator-(Vec3 const& left, Vec3 const& right) noexcept
{
    return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}

constexpr Vec3 operator-(Vec3&& left, Vec3 const& right) noexcept
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    
    return left;
}

constexpr Vec3 operator-(Vec3 const& left, Vec3&& right) noexcept
{
    return ::std::move(right) - left;
}

constexpr Vec3 operator-(Vec3&& left, Vec3&& right) noexcept
{
    return ::std::move(left) - right;
}

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
 * @brief 逆符号のベクトルを返す。
 *
 * @return Vec3
 */
constexpr Vec3 Vec3::operator-() const noexcept
{
    return Vec3(-x, -y, -z);
}

constexpr Vec3& Vec3::operator+=(const Vec3 &obj) noexcept
{
    x += obj.x;
    y += obj.y;
    z += obj.z;

    return *this;
}

constexpr Vec3& Vec3::operator-=(const Vec3 &obj) noexcept
{
    x -= obj.x;
    y -= obj.y;
    z -= obj.z;

    return *this;
}

/**
 * @brief ベクトルを定数倍する。
 *
 * @param num
 * @return Vec3
 */
constexpr Vec3 Vec3::timesScalar(double num) const noexcept
{
    return Vec3(x * num, y * num, z * num);
}

/**
 * @brief ベクトルの内積を返す。
 *
 * @param vec
 * @return double
 */
constexpr double Vec3::dot(Vec3 const& left, Vec3 const& right) noexcept
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

/**
 * @brief ベクトルの外積を返す。
 *
 * @param vec
 * @return Vec3
 */
constexpr Vec3 Vec3::cross(Vec3 vec) const noexcept
{
    return Vec3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

/**
 * @brief ベクトルを正規化する。ただし、長さが0の場合は0ベクトルを返す。
 *
 * @return Vec3
 */
inline Vec3 Vec3::normalize() const noexcept
{
    double len = this->length();

    if (len == 0) [[unlikely]] return Vec3(0, 0, 0);

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
 * @brief ゼロベクトルを返す。
 *
 * @return Vec3
 */
constexpr Vec3 Vec3::zero() noexcept
{
    return Vec3(0, 0, 0);
}

/**
 * @brief ベクトル同士の距離を返す。
 *
 * @param vec
 * @return double
 */
inline double Vec3::dist(Vec3 const& vec) const noexcept
{
    Vec3 diff = *this - vec;

    return diff.length();
}