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

        Numerics::Vector3 ComputeForceOnCell(
            const Simulation* sender,
            CellAlgorithmForceComputationArgs args
        ) const override;

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

        constexpr bool OverrideForceComputation() const noexcept override;
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

    constexpr bool NaiveAlgorithm::OverrideForceComputation() const noexcept
    {
        return true;
    }
}

#endif //!CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP