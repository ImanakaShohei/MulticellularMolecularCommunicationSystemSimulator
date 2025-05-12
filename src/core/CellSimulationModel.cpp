#include "CellSimulationModel.hpp"
#include <numbers>

void CellSimulationModel::initCells(::std::vector<UserCell*>& cells)
{
    std::mt19937 mt{ (uint32_t)SimulationSettings::CELL_SEED }; //!< 乱数生成器(生成器はとりあえずメルセンヌ・ツイスタ)
    const double fieldRadiusX = SimulationSettings::FIELD_X_LEN * 0.5;
    const double fieldRadiusY = SimulationSettings::FIELD_Y_LEN * 0.5;

    ::std::uniform_real_distribution<double> urd(0.0, 1.0);
    ::std::uniform_real_distribution<double> urdPi(0.0, ::std::numbers::pi * 2.0);

    if (fieldRadiusX == fieldRadiusY) [[likely]] {
        for (int32_t i = 0; i != SimulationSettings::CELL_NUM; i++) {
            double theta = urdPi(mt);
            double r = ::std::sqrt(urd(mt)) * fieldRadiusX;
            
            cells.push_back(new UserCell(CellType::WORKER, r * ::cos(theta), r * ::sin(theta), 10.0));
        }

        return;
    }
    
    // ここで fieldRadiusX != fieldRadiusY
    // 楕円内に同じ密度で敷き詰めるのは難しいのでとりあえず半径が小さいほうに合わせる

    const double minRidius = fieldRadiusX < fieldRadiusY ? fieldRadiusX : fieldRadiusY;

    for (int32_t i = 0; i != SimulationSettings::CELL_NUM; i++) {
        double theta = urdPi(mt);
        double r = ::std::sqrt(urd(mt)) * minRidius;
        
        cells.push_back(new UserCell(CellType::WORKER, r * ::cos(theta), r * ::sin(theta), 10.0));
    }
}