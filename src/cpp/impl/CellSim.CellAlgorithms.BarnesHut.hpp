#ifndef CELLSIM_CELLALGORITHMS_BARNESHUT_HPP
#define CELLSIM_CELLALGORITHMS_BARNESHUT_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim::CellAlgorithms
{
    /// @brief Baenes-Hut アルゴリズム
    class BarnesHut : public CellAlgorithm {
        private:

        // TODO: ここにメンバーを追加します
        
        public:

        BarnesHut();
        ~BarnesHut();

        void BeforeAdvanceStep(
            const Simulation* sender,
            CellAlgorithmStepArgs args
        ) override;

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
    };
}

#endif //!CELLSIM_CELLALGORITHMS_BARNESHUT_HPP