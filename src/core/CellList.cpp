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
#include "Simulation.hpp"

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
            cellField[y][x] = std::vector<UserCell*>();
        }
    }
}

/**
 * @brief 設定されたグリッドサイズに合わせてCellが入っているグリッドの座標(整数)を返却する。
 *
 * @param c
 * @return std::tuple<int32_t, int32_t>
 */
std::tuple<int32_t, int32_t> CellList::getGridCoordinateByCellPos(const UserCell& c) const
{
    Vec3 pos = c.getPosition();

    const int32_t gridX = (int32_t)((pos.x + SimulationSettings::FIELD_X_LEN / 2) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION);
    const int32_t gridY = (int32_t)((pos.y + SimulationSettings::FIELD_Y_LEN / 2) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION);

    return std::forward_as_tuple(gridX, gridY);
}

/**
 * @brief 指定したCellの周囲にあるCellのIDリストを返す。
 *
 * @param c
 * @return std::vector<int>
 * @note CHECK_WIDTHはcalcRemoteForceのLAMBDAより大きくするのが理想。
 */
std::vector<int32_t> CellList::aroundCellList(const UserCell& c) const
{
    std::vector<int32_t> aroundCells;
    const int32_t CHECK_GRID_WIDTH = (SimulationSettings::CELL_LIST_SEARCH_RADIUS + SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION - 1) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION; // 切り上げの割り算

    auto [gridX, gridY] = getGridCoordinateByCellPos(c);

    for (int32_t y = gridY - CHECK_GRID_WIDTH; y <= gridY + CHECK_GRID_WIDTH; y++) {
        for (int32_t x = gridX - CHECK_GRID_WIDTH; x <= gridX + CHECK_GRID_WIDTH; x++) {
            if (!isInGrid(x, y)) { // グリッド外を参照している場合は飛ばす
                continue;
            }

            int32_t size = (int32_t)cellField[y][x].size();

            for (int32_t i = 0; i < size; i++) {
                if (checkInSearchRadius(c.getPosition(), cellField[y][x][i]->getPosition())) {
                    aroundCells.emplace_back(cellField[y][x][i]->arrayIndex);
                }
            }
        }
    }

    return aroundCells;
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
void CellList::addCell(UserCell* cell)
{
    Vec3 pos = cell->getPosition();

    const int32_t scaledY = (int32_t)((pos.y + SimulationSettings::FIELD_Y_LEN / 2) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION);
    const int32_t scaledX = (int32_t)((pos.x + SimulationSettings::FIELD_X_LEN / 2) / SimulationSettings::CELL_LIST_GRID_SIZE_MAGNIFICATION);

    cellField[scaledY][scaledX].emplace_back(cell);
}

Vec3 CellList::calcCellForce(UserCell& c, ::std::vector<UserCell*> const& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    auto aroundCells = this->aroundCellList(c);
    Vec3 force       = Vec3::zero();

    switch (c.getCellType()) {
        case CellType::WORKER:
            for (auto i : aroundCells) {
                if (cells[i]->getCellType() == CellType::WORKER) {
                    force += Simulation::calcRemoteForce(c, *cells[i]);
                }
            }
            force = force.normalize();

            for (auto i : aroundCells) {
                if (cells[i]->getCellType() != CellType::NONE) {
                    force += Simulation::calcVolumeExclusion(c, *cells[i]);
                }
            }

            return force.timesScalar(SimulationSettings::DELTA_TIME);

        case CellType::DEAD:
            for (auto i : aroundCells) {
                if (cells[i]->getCellType() != CellType::NONE) {
                    force += Simulation::calcVolumeExclusion(c, *cells[i]);
                }
            }

            return force.timesScalar(SimulationSettings::DELTA_TIME);

        case CellType::NONE:
            return Vec3::zero();
        default:
            std::cerr << "CellType is Wrong: " << NAMEOF_ENUM(c.getCellType()) << std::endl;
            exit(1);
    }
}

void CellList::setCells(const ::std::vector<UserCell*>& cells)
{
    resetGrid();

    for (auto&& cell : cells) {
        addCell(cell);
    }
}

void CellList::beforeNextStep(const ::std::vector<::UserCell*>& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    setCells(cells);
}