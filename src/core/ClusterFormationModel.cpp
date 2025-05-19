#include "ClusterFormationModel.hpp"

void ClusterFormationModel::beforeNextStep(::std::vector<UserCell*>& cells, ::std::vector<UserMoleculeSpace*>& moleculeSpaces)
{
    // すべての細胞の力を初期化する(速度を0に設定)
    for (auto pCell : cells) {
        pCell->initForce();
    }

    for (auto pCell : cells) {
        UserCell& c = *pCell;

        switch (c.getCellType()) {
            case CellType::DEAD:
            case CellType::NONE:
                break;

            default:
                c.metabolize();
                break;
        }
    }

    // 要素数の変更があるので連想for文は使わない
    for (uint32_t i = 0; i < cells.size(); i++) {
        UserCell& cell = *cells[i];

        switch (cell.getCellType()) {
            case CellType::DEAD:
            case CellType::NONE:
                break;

            default:
            {
                if (!cell.checkWillDivide()) break;
                
                UserCell* c = new UserCell(cell.divide());
                
                // 分裂した場合は配列に新しいCellを上書き(あるいは追加)する。
                if (c->arrayIndex >= (int32_t)cells.size()) {
                    cells.push_back(c);
                }
                else {
                    cells[c->arrayIndex] = c;
                }
                
                break;
            }
        }
    }

    CellSimulationModel::beforeNextStep(cells, moleculeSpaces);
}