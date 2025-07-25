#include "CellSim.CellAlgorithms.ClusterModel.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmAffectableCellQueryArgs.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellList.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.Cells.CellInfo.hpp"

namespace CellSim::CellAlgorithms
{
    void ClusterModel::Combine(::std::vector<Cells::Cell>& cells, ::std::vector<Molecular::MoleculeField> const& fields, const CellList* pCellList)
    {
        auto f = [] (Cells::Cell& cell, Cells::CellInfo info, Cells::CellInfo cellInfo) {
            if (cellInfo.Type == Cells::CellType::Invalid()) return;
            if (cellInfo.Type != info.Type) return;

            double radius = info.Radius + cellInfo.Radius;

            //距離 < 細胞半径 + 細胞半径 でくっつく
            //高速化のため、２乗で計算
            if ((info.Position - cellInfo.Position).SquareLength() < radius * radius) {
                cell.Combine(*const_cast<Cells::Cell*>(cellInfo.CellPtr));
            }
        };

        if (pCellList == nullptr) {
            for (auto itr1 = cells.begin(), end = cells.end(); itr1 != end; ++itr1) {
                Cells::CellInfo info{ *itr1 };

                for (auto itr2 = itr1 + 1; itr2 != end; ++itr2) {
                    f(*itr1, info, *itr2);
                }
            }
        }
        else {
            for (auto itr1 = cells.begin(), end = cells.end(); itr1 != end; ++itr1) {
                Cells::Cell& cell = *itr1;
                Cells::CellInfo info{ cell };
                

                CELLSIM_CELLALGORITHMS_CELLALGORITHM_ITERATE_EX(
                    cellInfo,
                    pCellList,
                    nullptr,
                    &cell,
                    &cells,
                    &fields,
                    {
                        f(cell, info, cellInfo);
                    }
                )
            }
        }

        
    }
}