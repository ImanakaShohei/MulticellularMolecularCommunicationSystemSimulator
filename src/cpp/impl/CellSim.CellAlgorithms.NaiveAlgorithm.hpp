#ifndef CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP
#define CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim::CellAlgorithms
{
    /// @brief ナイーブなアルゴリズム
    class NaiveAlgorithm : public CellAlgorithm {
        public:

        void ApplyInteraction(
            const Simulation* sender,
            CellAlgorithmInteractionArgs args
        ) override;

        void BeforeAdvanceStep(
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

        bool HasMultithreadingSupport() const noexcept override;

        Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            const Model::CellSimulationModel* sender,
            CellAlgorithmAffectableCellQueryArgs args
        ) const override;

        void OnAdvanceStep(
            const Simulation* sender,
            CellAlgorithmStepArgs args
        ) override;

        bool OverrideForceComputation() const noexcept override;
        bool OverrideInteraction() const noexcept override;
    };
}

#endif //!CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP