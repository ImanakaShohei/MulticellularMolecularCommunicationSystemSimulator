#include "Vec3.hpp"
#include <numbers>

/**
 * @brief ベクトルを方位角theta,
 * 天頂角phiで回転させたベクトルを返す。若干重い定数倍計算量なので注意。
 *
 * @param theta
 * @param phi
 * @return Vec3
 * @note これ未完成なところがあるので注意。使う必要もない気がする。
 */
Vec3 Vec3::rotate(double theta, double phi) const noexcept
{
    double rotatedPos[3] = { x, y, z };

    double rotate[3][3] = { { std::cos(theta) * std::cos(phi), std::sin(theta) * std::cos(phi), -std::sin(phi) },
                            { -std::sin(theta), std::cos(theta), 0 },
                            { std::cos(theta) * std::sin(phi), std::sin(theta) * std::sin(phi), std::cos(phi) } };

    double v[3] = { rotatedPos[0], rotatedPos[1], rotatedPos[2] };
    for (int y_i = 0; y_i < 3; y_i++) {
        double sum = 0;

        for (int x_i = 0; x_i < 3; x_i++) {
            sum += rotate[y_i][x_i] * v[x_i];
        }
        rotatedPos[y_i] = sum;
    }

    return Vec3(rotatedPos[0], rotatedPos[1], rotatedPos[2]);
}

/**
 * @brief ベクトルの成分を出力する。デバッグ用途。
 *
 */
void Vec3::print() const noexcept
{
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

/**
 * @brief ランダムの方向(二次元単位ベクトル)を返す。
 *
 */
Vec3 Vec3::randomDirection2() noexcept
{
    static std::mt19937 rand_gen(0);                          //!< 乱数生成器(生成器はとりあえずメルセンヌ・ツイスタ)
    std::uniform_real_distribution<double> angle_ratio(0, 1); //!< 方向の割合
    double angle = 2.0 * std::numbers::pi * angle_ratio(rand_gen);

    return Vec3(std::cos(angle), std::sin(angle), 0);
}

// TODO: 動作未確認！テスト作るべし!
/**
 * @brief ランダムの方向(三次元単位ベクトル)を返す。
 *
 * @return Vec3
 */
Vec3 Vec3::randomDirection3() noexcept
{
    static std::mt19937 rand_gen(0);                          //!< 乱数生成器(生成器はとりあえずメルセンヌ・ツイスタ)
    std::uniform_real_distribution<double> angle_ratio(0, 1); //!< 方向の割合
    double theta = 2.0 * std::numbers::pi * angle_ratio(rand_gen);
    double phi   = 2.0 * std::numbers::pi * angle_ratio(rand_gen);

    return Vec3(std::cos(theta) * std::sin(phi), std::sin(theta) * std::sin(phi), std::cos(phi));
}