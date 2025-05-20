#include "ClusterModel.hpp"
#include "Simulation.hpp"

void ClusterModel::combine(const ::std::vector<Cell*>& cells, const ::std::vector<UserMoleculeSpace*>&)
{
    size_t length = cells.size();
    //細胞同士が十分に近ければくっついたと判定する
    for (size_t i = 0; i < length; ++i) {
        Cell& cell = *cells[i];
        switch (cell.getCellType()) {
            case CellType::WORKER:
            {
                for (size_t j = i + 1; j < length; j++) {

                    Cell& cellr = *cells[j];

                    if (cellr.getCellType() != CellType::WORKER) continue;
        
                    //
                    double radius = cell.getRadius() + cellr.getRadius();
        
                    //距離 < 細胞半径 + 細胞半径 でくっつく
                    //高速化のため、２乗で計算
                    if ((cell.getPosition() - cellr.getPosition()).squareLength() < radius * radius) {
                        cell.combine(cellr);
                        continue;
                    }
                }
                break;
            }

            default: break;
        }
        
    }
}

void ClusterModel::combine(const ::std::vector<Cell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces, CellList& cellList)
{
    size_t length = cells.size();
    //細胞同士が十分に近ければくっついたと判定する
    for (size_t i = 0; i < length; ++i) {
        Cell& cell = *cells[i];
        CellInfo info = CellInfo(cell);

        switch (info.cellType) {
            case CellType::WORKER:
            {
                auto f = [] (Cell& cell, CellInfo info, CellInfo cellInfo) {
                    if (cellInfo.cellType != CellType::WORKER) return;
        
                    double radius = info.radius + cellInfo.radius;
        
                    //距離 < 細胞半径 + 細胞半径 でくっつく
                    //高速化のため、２乗で計算
                    if ((info.position - cellInfo.position).squareLength() < radius * radius) {
                        cell.combine(*cellInfo.pCell);
                    }
                };

                switch (SimulationSettings::PERFORMANCE) {
                    case PerformanceKind::HighPerformance:
                    {
                        for (CellInfo cellInfo : cellList.getAffectableCellInfos(cell, cells, moleculeSpaces)) {
                            f(cell, info, cellInfo);
                        }
                        break;
                    }
                    case PerformanceKind::LowMemory:
                    {
                        for (CellInfo cellInfo : cellList.iterateAffectableCellInfos(cell, cells, moleculeSpaces)) {
                            f(cell, info, cellInfo);
                        }
                        break;
                    }
                }
                
                break;
            }

            default: break;
        }
        
    }
}

void ClusterModel::combine(const ::std::vector<Cell*>& cells, const ::std::vector<UserMoleculeSpace*>& moleculeSpaces, CellList* pCellList)
{
    if (pCellList == nullptr) combine(cells, moleculeSpaces);
    else combine(cells, moleculeSpaces, *pCellList);
}