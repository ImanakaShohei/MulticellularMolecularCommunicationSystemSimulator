#pragma once

#include "DiffusionMoleculeSpace.hpp"

/// @brief 信号分子拡散モデル
class SignalDiffusionMoleculeSpace : public DiffusionMoleculeSpace {
    private:

    double m_hydrolysisCoefficient;

    public:

    SignalDiffusionMoleculeSpace(
        const uint64_t moleculeNum,
        const MoleculeDistributionType distributionType,
        const MoleculeSpaceBorderType borderType,
        std::vector<Cell*>* cells,
        const uint32_t ID
    );

    void calcConcentrationDiff() noexcept override;
};