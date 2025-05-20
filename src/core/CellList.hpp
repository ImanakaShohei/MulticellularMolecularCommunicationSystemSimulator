/**
 * @file CellList.hpp
 * @author Takanori Saiki
 * @brief CellListのデータ構造を管理するクラス
 * @version 0.1
 * @date 2022-06-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../SimulationSettings.hpp"
#include "../UserCell.hpp"
#include "../utils/Util.hpp"
#include "../utils/Vec3.hpp"
#include "CellAlgorithm.hpp"
#include <memory>
#include <tuple>
#include <vector>

class CellList : public CellAlgorithm
{
  private:
    Field<std::vector<Cell*>> cellField; //!< セルのポインタが格納されている2次元配列

    std::tuple<int32_t, int32_t> getGridCoordinateByCellPos(const Cell& c) const;

    const int32_t CELL_GRID_LEN_X;
    const int32_t CELL_GRID_LEN_Y;

  public:
    CellList();
    ~CellList();

    void init();
    constexpr bool isInGrid(const int32_t x, const int32_t y) const noexcept;
    static bool checkInSearchRadius(const Vec3& v, const Vec3& u) noexcept;
    void resetGrid() noexcept;
    void addCell(Cell* cell);
    void setCells(const ::std::vector<Cell*>& cells);
    //  周辺のCellのIDを格納する。ただし、vectorは一列分のみしか確保しない。
    void beforeNextStep(const ::std::vector<Cell*>& cells, const ::std::vector<UserMoleculeSpace*>&) override;
    Generator<CellInfo> iterateAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
    ::std::vector<CellInfo> getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces) override;
};

/**
 * @brief 指定されたグリッド座標(x, y)がグリッドの定義域に存在するかを返す。
 *
 * @param x
 * @param y
 * @return bool
 */
constexpr bool CellList::isInGrid(const int32_t x, const int32_t y) const noexcept
{
  return (0 <= x && x < CELL_GRID_LEN_X) && (0 <= y && y < CELL_GRID_LEN_Y);
}

/**
 * @brief UserCell cの範囲内にCell dが存在するかを返す。ただし、c == dのときもfalseにする。
 *
 * @param c
 * @param d
 * @return true
 * @return false
 */
inline bool CellList::checkInSearchRadius(const Vec3& v, const Vec3& u) noexcept
{
    return (v - u).squareLength() < SimulationSettings::CELL_LIST_SEARCH_RADIUS * SimulationSettings::CELL_LIST_SEARCH_RADIUS;
}