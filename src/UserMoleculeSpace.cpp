#include "UserMoleculeSpace.hpp"

UserMoleculeSpace::UserMoleculeSpace(const uint64_t moleculeNum, const MoleculeDistributionType distributionType, const MoleculeSpaceBorderType borderType,
                                     std::vector<UserCell*>& cells, const uint32_t ID)
  : MoleculeSpace(moleculeNum, distributionType, borderType, cells, ID, 0.024 * 1000000.0)
{
}

UserMoleculeSpace::~UserMoleculeSpace()
{
}

void UserMoleculeSpace::calcConcentrationDiff() noexcept
{
    // 毎ステップ実行されることを考えると控えめな値にしておいた方がいい。あるいは細胞側の放出量を増やす
    constexpr double hydrolysisCoefficient = 5.4;

    // すべての格子について拡散、生成、分解、移流を行う
    // #pragma omp parallel for
    for (uint32_t x = 1; x <= width; x++) {
        for (uint32_t y = 1; y <= height; y++) {
            for (uint32_t z = 1; z <= depth; z++) {
                deltaMoleculeSpace[x][y][z] = diffuse(x, y, z);
                deltaMoleculeSpace[x][y][z] += -hydrolysisCoefficient * moleculeSpace[x][y][z];
            }
        }
    }

    // FIXME: cellsの数は常に変化するので、vectorへの参照を持っておく方がいい
    // 細胞からの放出を加える
    const int32_t width  = SimulationSettings::FIELD_X_LEN;
    const int32_t height = SimulationSettings::FIELD_Y_LEN;
    const int32_t depth  = SimulationSettings::FIELD_Z_LEN;

    // #pragma omp parallel for
    for (uint32_t i = 0; i < cells.size(); i++) {
        UserCell& cell = *cells[i];
        auto position = cell.getPosition();

        int32_t x = (int32_t)((position.x + width / 2) / dr) + 1;
        int32_t y = (int32_t)((position.y + height / 2) / dr) + 1;
        int32_t z = (int32_t)((position.z + depth / 2) / dr) + 1;

        // #pragma omp atomic
        deltaMoleculeSpace[x][y][z] += cell.emitMolecule(ID);
    }
}

void UserMoleculeSpace::nextStep() noexcept
{
    // #pragma omp parallel for
    for (uint32_t x = 1; x <= width; x++) {
        for (uint32_t y = 1; y <= height; y++) {
            for (uint32_t z = 1; z <= depth; z++) {
                moleculeSpace[x][y][z] += deltaMoleculeSpace[x][y][z] * SimulationSettings::DELTA_TIME;
                // deltaMoleculeSpace[x][y][z] = 0.0;
            }
        }
    }

    setupBoundary(moleculeSpace, borderType);
}