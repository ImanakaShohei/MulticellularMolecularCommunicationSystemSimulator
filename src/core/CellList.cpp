/**
 * @file CellList.cpp
 * @author Takanori Saiki
 * @brief CellListのデータ構造を管理するクラス
 * @version 0.1
 * @date 2022-06-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "CellList.hpp"

/**
 * @brief CellListの初期化を呼びだす。
 *
 */
CellList::CellList()
  : CELL_GRID_LEN_X(SimulationSettings::FIELD_X_LEN / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION)
  , CELL_GRID_LEN_Y(SimulationSettings::FIELD_Y_LEN / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION)
{
    init();
}

CellList::~CellList()
{
}

/**
 * @brief CellListのサイズを初期化する。
 *
 */
void CellList::init()
{
    cellField.resize(CELL_GRID_LEN_Y);
    for (int32_t y = 0; y < CELL_GRID_LEN_Y; y++) {
        cellField[y].resize(CELL_GRID_LEN_X);

        // 消すべき？
        for (int32_t x = 0; x < CELL_GRID_LEN_X; x++) {
            cellField[y][x] = std::vector<Cell*>();
        }
    }
}

/**
 * @brief 設定されたグリッドサイズに合わせてCellが入っているグリッドの座標(整数)を返却する。
 *
 * @param c
 * @return std::tuple<int32_t, int32_t>
 */
std::tuple<int32_t, int32_t> CellList::getGridCoordinateByCellPos(const Cell& c) const
{
    Vec3 pos = c.getPosition();

    const int32_t gridX = (int32_t)((pos.x + SimulationSettings::FIELD_X_LEN / 2) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION);
    const int32_t gridY = (int32_t)((pos.y + SimulationSettings::FIELD_Y_LEN / 2) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION);

    return std::forward_as_tuple(gridX, gridY);
}

/**
 * @brief 指定したCellの周囲にあるCellのinfoを返す
 *
 * @param c
 * @return std::vector<int>
 * @note CHECK_WIDTHはcalcRemoteForceのLAMBDAより大きくするのが理想。
 */
Generator<CellInfo> CellList::iterateAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>&)
{
    static const int32_t CHECK_GRID_WIDTH = (SimulationSettings::CELL_LIST_SEARCH_RADIUS + SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION - 1) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION; // 切り上げの割り算

    auto [gridX, gridY] = getGridCoordinateByCellPos(c);

    auto yMax = gridY + CHECK_GRID_WIDTH;
    auto xMax = gridX + CHECK_GRID_WIDTH;

    for (int32_t y = gridY - CHECK_GRID_WIDTH; y <= yMax; y++) {
        for (int32_t x = gridX - CHECK_GRID_WIDTH; x <= xMax; x++) {
            if (!isInGrid(x, y)) { // グリッド外を参照している場合は飛ばす
                continue;
            }

            auto& field = cellField[y][x];
            int32_t size = (int32_t)field.size();
            
            for (int32_t i = 0; i < size; i++) {
                Cell& cell = *field[i];
                
                if (&cell == &c) continue;

                if (checkInSearchRadius(c.getPosition(), cell.getPosition())) {
                    co_yield CellInfo(cell);
                }
            }
        }
    }
    
}

// コピペはよくないので良い方法を考える
::std::vector<CellInfo> CellList::getAffectableCellInfos(Cell& c, ::std::vector<Cell*> const& cells, const ::std::vector<MoleculeSpace*>& moleculeSpaces)
{
    ::std::vector<CellInfo> list;
    static const int32_t CHECK_GRID_WIDTH = (SimulationSettings::CELL_LIST_SEARCH_RADIUS + SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION - 1) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION; // 切り上げの割り算

    auto [gridX, gridY] = getGridCoordinateByCellPos(c);

    auto yMax = gridY + CHECK_GRID_WIDTH;
    auto xMax = gridX + CHECK_GRID_WIDTH;

    for (int32_t y = gridY - CHECK_GRID_WIDTH; y <= yMax; y++) {
        for (int32_t x = gridX - CHECK_GRID_WIDTH; x <= xMax; x++) {
            if (!isInGrid(x, y)) { // グリッド外を参照している場合は飛ばす
                continue;
            }

            auto& field = cellField[y][x];
            int32_t size = (int32_t)field.size();
            
            for (int32_t i = 0; i < size; i++) {
                Cell& cell = *field[i];
                if (&cell == &c) continue;
                if (checkInSearchRadius(c.getPosition(), cell.getPosition())) {
                    list.emplace_back(cell);
                }
            }
        }
    }

    return list;
}

/**
 * @brief CellListに保存されているCellの配列をすべて削除する。
 *
 */
void CellList::resetGrid() noexcept
{
    for (auto&& vec2 : cellField) {
        for (auto&& vec : vec2) {
            vec.clear();
        }
    }
}

/**
 * @brief CellListのグリッドにCellのポインタを登録する。
 *
 * @param cell
 */
void CellList::addCell(Cell* cell)
{
    Vec3 pos = cell->getPosition();

    const int32_t scaledY = (int32_t)((pos.y + SimulationSettings::FIELD_Y_LEN / 2) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION);
    const int32_t scaledX = (int32_t)((pos.x + SimulationSettings::FIELD_X_LEN / 2) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION);
    
    cellField[scaledY][scaledX].emplace_back(cell);
}

void CellList::setCells(const ::std::vector<Cell*>& cells)
{
    resetGrid();
    
    for (auto cell : cells) {
        addCell(cell);
    }
}

void CellList::beforeNextStep(const ::std::vector<::Cell*>& cells, const ::std::vector<MoleculeSpace*>&)
{
    setCells(cells);
}