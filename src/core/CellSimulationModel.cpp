#include "CellSimulationModel.hpp"

void CellSimulationModel::initCells(::std::vector<UserCell*>& cells)
{
    std::mt19937 rand_gen{ (uint32_t)SimulationSettings::CELL_SEED }; //!< 乱数生成器(生成器はとりあえずメルセンヌ・ツイスタ)
    std::uniform_real_distribution<> randomCellPosX(-SimulationSettings::FIELD_X_LEN / 2, SimulationSettings::FIELD_X_LEN / 2);        //!< Cellのx座標の生成器
    std::uniform_real_distribution<> randomCellPosY(-SimulationSettings::FIELD_Y_LEN / 2, SimulationSettings::FIELD_Y_LEN / 2);        //!< Cellのy座標の生成器

    for (int32_t i = 0; i != SimulationSettings::CELL_NUM; i++) {
        double xPos = randomCellPosX(rand_gen);
        double yPos = randomCellPosY(rand_gen);
        
        cells.push_back(new UserCell(CellType::WORKER, xPos, yPos, 10.0));
    }
}