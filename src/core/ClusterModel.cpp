#include "ClusterModel.hpp"
#include "Simulation.hpp"

void ClusterModel::onNextStep(const ::std::vector<::std::shared_ptr<UserCell>>& cells)
{
    size_t length = cells.size();
    //細胞同士が十分に近ければくっついたと判定する
    for (size_t i = 0; i < length; ++i) {
        UserCell& cell = *cells[i];
        switch (cell.getCellType()) {
            case CellType::WORKER:
            {
                for (size_t j = i + 1; j < length; j++) {

                    UserCell& cellr = *cells[j];

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