#ifndef CELLSIM_CELLALGORITHMS_PARTICLEMESH_HPP
#define CELLSIM_CELLALGORITHMS_PARTICLEMESH_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim::CellAlgorithms
{
    /// @brief PM法
    class ParticleMesh : public CellAlgorithm {
        private:

        // TODO: ここにメンバーを追加します

        public:

        // 引数を追加してはいけない
        ParticleMesh();
        ~ParticleMesh();

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
    };
}

#endif //!CELLSIM_CELLALGORITHMS_PARTICLEMESH_HPP