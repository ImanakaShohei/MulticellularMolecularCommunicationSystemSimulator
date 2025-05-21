#pragma once

#include "DiffusionMoleculeSpace.hpp"

class SignalDiffusionMoleculeSpace : public DiffusionMoleculeSpace {
    private:

    static constexpr double s_D = 0.024 * 1000000.0;

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