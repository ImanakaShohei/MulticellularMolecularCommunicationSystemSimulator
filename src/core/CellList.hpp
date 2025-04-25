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
    Field<std::vector<std::shared_ptr<UserCell>>> cellField; //!< セルのポインタが格納されている2次元配列

    std::tuple<int32_t, int32_t> getGridCoordinateByCellPos(const std::shared_ptr<UserCell> c) const;

    const int32_t CELL_GRID_LEN_X;
    const int32_t CELL_GRID_LEN_Y;

  public:
    CellList();
    ~CellList();

    void init();
    std::vector<int32_t> aroundCellList(const std::shared_ptr<UserCell> c) const;
    bool isInGrid(const int32_t x, const int32_t y) const;
    bool checkInSearchRadius(const Vec3 v, const Vec3 u) const;
    void resetGrid() noexcept;
    void addCell(const std::shared_ptr<UserCell>& cell);
    Vec3 calcCellForce(const ::std::shared_ptr<UserCell>& c, ::std::vector<::std::shared_ptr<UserCell>> const& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) const noexcept override;
    //  周辺のCellのIDを格納する。ただし、vectorは一列分のみしか確保しない。
    void beforeNextStep(const ::std::vector<::std::shared_ptr<UserCell>>& cells, const ::std::vector<::std::unique_ptr<UserMoleculeSpace>>&) override;
};
