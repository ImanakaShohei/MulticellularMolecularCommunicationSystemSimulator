#ifndef CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP
#define CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithmStepArgs.hpp"

namespace CellSim::CellAlgorithms
{
    class NaiveAlgorithm : public CellAlgorithm {
        public:

        constexpr void BeforeAdvanceStep(
            const Simulation* sender,
            CellAlgorithmStepArgs args
        ) override;

        ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            const Model::CellSimulationModel* sender,
            CellAlgorithmAffectableCellQueryArgs args
        ) const override;

        constexpr bool HasMultithreadingSupport() const noexcept override;

        Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            const Model::CellSimulationModel* sender,
            CellAlgorithmAffectableCellQueryArgs args
        ) const override;

        constexpr void OnAdvanceStep(
            const Simulation* sender,
            CellAlgorithmStepArgs args
        ) override;
    };
}

namespace CellSim::CellAlgorithms
{
    constexpr void NaiveAlgorithm::BeforeAdvanceStep(
            const Simulation*,
            CellAlgorithmStepArgs
    )
    {
    }

    constexpr bool NaiveAlgorithm::HasMultithreadingSupport() const noexcept
    {
        return true;
    }

    constexpr void NaiveAlgorithm::OnAdvanceStep(
            const Simulation*,
            CellAlgorithmStepArgs
    )
    {
    }
}

#endif //!CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP