#include "SignalDiffusionMoleculeSpace.hpp"
#include "SignalDiffusionCell.hpp"

#include "../SimulationSettings.hpp"

SignalDiffusionMoleculeSpace::SignalDiffusionMoleculeSpace(
    const uint64_t moleculeNum,
    const MoleculeDistributionType distributionType,
    const MoleculeSpaceBorderType borderType,
    std::vector<Cell*>* cells,
    const uint32_t ID
)
    : DiffusionMoleculeSpace(
        moleculeNum,
        distributionType,
        borderType,
        cells,
        ID,
        SimulationSettings::SMD_DIFFUSION_COEFFICIENT
    )
    , m_hydrolysisCoefficient(SimulationSettings::SMD_HYDROLYSYS_COEFFICIENT)
{
}

void SignalDiffusionMoleculeSpace::calcConcentrationDiff() noexcept
{

    // すべての格子について拡散、生成、分解、移流を行う
    // #pragma omp parallel for
    for (uint32_t x = 1; x <= width; x++) {
        for (uint32_t y = 1; y <= height; y++) {
            for (uint32_t z = 1; z <= depth; z++) {
                deltaMoleculeSpace[x][y][z] = diffuse(x, y, z) - m_hydrolysisCoefficient * moleculeSpace[x][y][z];
            }
        }
    }

    // FIXME: cellsの数は常に変化するので、vectorへの参照を持っておく方がいい
    // 細胞からの放出を加える
    const int32_t width  = SimulationSettings::FIELD_X_LEN;
    const int32_t height = SimulationSettings::FIELD_Y_LEN;
    const int32_t depth  = SimulationSettings::FIELD_Z_LEN;

    // #pragma omp parallel for
    for (Cell* pCell : *pCells) {
        auto position = pCell->getPosition();

        int32_t x = (int32_t)((position.x + width / 2) / dr) + 1;
        int32_t y = (int32_t)((position.y + height / 2) / dr) + 1;
        int32_t z = (int32_t)((position.z + depth / 2) / dr) + 1;

        //deltaMoleculeSpace[x][y][z] += pCell->emitMolecule(ID);
        deltaMoleculeSpace[x][y][z] += 1;
    }

    for (Cell* pCell : *pCells) {
        auto position = pCell->getPosition();

        int32_t x = (int32_t)((position.x + width / 2) / dr) + 1;
        int32_t y = (int32_t)((position.y + height / 2) / dr) + 1;
        int32_t z = (int32_t)((position.z + depth / 2) / dr) + 1;

        static_cast<SignalDiffusionCell*>(pCell)->setDiffState(moleculeSpace[x][y][z]);
    }
}