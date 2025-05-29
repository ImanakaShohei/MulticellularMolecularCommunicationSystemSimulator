/**
 * @file Cell.hpp
 * @author Takanori Saiki
 * @brief Cell class
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../CellType.hpp"
#include "../utils/Vec3.hpp"
#include <queue>
#include <random>
#include <vector>
#include <iosfwd>

class MoleculeSpace;

/**
 * @class Cell
 * @brief Cell単体の状態を管理するクラス
 */
class Cell
{
  protected:
    CellType typeID; //!< Cellの種類
    Vec3 position;   //!< Cellの座標(x,y,z)
    Vec3 addedForce;   //!< Cellにくわえられた力
    Vec3 previusAddedForce;
    double weight;   //!< Cellの質量
    double radius;   //!< Cellの半径

    std::vector<const Cell*> adhereCells; //!< 接着しているCellのポインタを格納する配列

    std::vector<MoleculeSpace*> moleculeSpaces; //!< 分子空間のポインタを格納する配列
    std::vector<int> molecularStocks;           //!< 細胞の保持している分子数。配列の添字は分子の種類。

    int32_t releaseIndex() noexcept;

    void adjustPosInField() noexcept;

  private:
    static int32_t upperOfCellCount; //!< 同時に存在していた細胞の上限数。static変数。

    std::queue<Vec3> preVelocitiesQueue; //!< 速度計算用のキュー

    // Simulation *sim; //!< Cellの呼び出し元になるSimulationインスタンスのポインタ
    static Vec3 calcVelocity(std::queue<Vec3>& velocities) noexcept;
    static Vec3 calcAB4(std::queue<Vec3>& velocities) noexcept;
    static Vec3 calcAB3(std::queue<Vec3>& velocities) noexcept;
    static Vec3 calcAB2(std::queue<Vec3>& velocities) noexcept;
    static Vec3 calcEuler(std::queue<Vec3>& velocities) noexcept;
    static Vec3 calcOriginal(std::queue<Vec3>& velocities) noexcept;

  public:
    Cell();
    Cell(CellType _typeID, double x, double y, double radius = 5.0, double vx = 0, double vy = 0);
    Cell(CellType _typeID, Vec3 pos, double radius = 5.0, Vec3 v = Vec3::zero());
    virtual ~Cell();

    static double calcRadiusFromVolume(double volume) noexcept;
    static double calcVolumeFromRadius(double radius) noexcept;

    constexpr Vec3 getAddedForce() const noexcept;
    constexpr Vec3 getPreviusAddedForce() const noexcept;
    constexpr CellType getCellType() const noexcept;
    constexpr Vec3 getPosition() const noexcept;
    constexpr Vec3 getVelocity() const noexcept;
    constexpr double getWeight() const noexcept;
    constexpr double getRadius() const noexcept;
    constexpr double setRadius(double r);

    void initForce() noexcept;
    constexpr void addForce(double fx, double fy) noexcept;
    constexpr void addForce(const Vec3& f) noexcept;
    void nextStep() noexcept;

    void clearAdhereCells() noexcept;
    void adhere(const Cell& c) noexcept;
    constexpr size_t adhereCellsCount() const noexcept;
    constexpr bool isAdhere(const Cell* pCell) const noexcept;

    virtual bool checkWillDie() const noexcept;    // ユーザが定義
    virtual bool checkWillDivide() const noexcept; // ユーザが定義
    virtual void metabolize() noexcept;            // ユーザが定義
    virtual int32_t die() noexcept;                // ユーザが定義
    Cell divide() noexcept;                        // オーバーライドして使う。

    // 細胞が結合する
    void combine(Cell& cell) noexcept;

    virtual double emitMolecule(int moleculeId) noexcept;
    virtual double absorbMolecule(int moleculeId, double amountOnTheSpot) noexcept;

    static int32_t getNewCellIndex() noexcept;

    void printCell(::std::ostream& out) const;
    void printDebug() const noexcept; // デバッグ用

    static int32_t numberOfCellsBorn; //!< 今までに生成した生きているCellの数。static変数。
    static std::queue<int> cellPool;  //!< CellのIDを管理するためのキュー

    const int id;         //!< CellのID
    const int arrayIndex; //!< 配列のどこに入るか
};

/**
 * @brief Cellに加えられた力を返す
 *
 * @return Vec3 Cellの座標
 */
constexpr Vec3 Cell::getAddedForce() const noexcept
{
    return addedForce;
}

/**
 * @brief 1step前に加えられて力を取得
 *
 * @return Vec3 Cellの座標
 */
constexpr Vec3 Cell::getPreviusAddedForce() const noexcept
{
    return previusAddedForce;
}

/**
 * @brief CellのIDを返す。必ず副作用をつけない点に注意。
 *
 * @return int CellのID
 */
constexpr CellType Cell::getCellType() const noexcept
{
    return typeID;
}

/**
 * @brief Cellの座標を返す。必ず副作用をつけない点に注意。
 *
 * @return Vec3 Cellの座標
 */
constexpr Vec3 Cell::getPosition() const noexcept
{
    return position;
}

/**
 * @brief Cellの速度を返す。必ず副作用をつけない点に注意。
 *
 * @return Vec3 Cellの速度
 */
constexpr Vec3 Cell::getVelocity() const noexcept
{
    return addedForce / weight;
}

/**
 * @brief Cellの質量を返す。必ず副作用をつけない点に注意。
 *
 * @return double Cellの質量
 */
constexpr double Cell::getWeight() const noexcept
{
    return weight;
}

/**
 * @brief Cellの半径を返す。必ず副作用をつけない点に注意。
 *
 * @return double Cellの半径
 */
constexpr double Cell::getRadius() const noexcept
{
    return radius;
}

/**
 * @brief Cellの半径を設定する。
 *
 * @param r Cellの半径
 * @return double Cellの半径
 */
constexpr double Cell::setRadius(double r)
{
    if (r < 0.0) [[unlikely]] {
        throw std::invalid_argument("Cell::setRadius() : radius must be positive.");
    }
    radius = r;

    return radius;
}

/**
 * @brief Cellにかかっている力を初期化する。
 *
 */
inline void Cell::initForce() noexcept
{
    addedForce = Vec3::zero();
}

/**
 * @brief Cellに力を加える(double型)。このモデルでは力はそのまま速度になる。
 *
 * @param fx x方向の力
 * @param fy y方向の力
 */
constexpr void Cell::addForce(double fx, double fy) noexcept
{
    addedForce.x += fx;
    addedForce.y += fy;
}

/**
 * @brief Cellに力を加える(Vec3型)。このモデルでは力はそのまま速度になる。
 *
 * @param f
 */
constexpr void Cell::addForce(const Vec3& f) noexcept
{
    addedForce += f;
}

constexpr size_t Cell::adhereCellsCount() const noexcept
{
    return adhereCells.size();
}

constexpr bool Cell::isAdhere(const Cell* pCell) const noexcept
{
    for (const Cell* p : adhereCells) {
        if (p == pCell) return true;
    }

    return false;
}