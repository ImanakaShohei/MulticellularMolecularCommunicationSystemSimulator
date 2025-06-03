#ifndef CELLSIM_MODEL_CLUSTERSPROUTINGMODEL_HPP
#define CELLSIM_MODEL_CLUSTERSPROUTINGMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Model
{
    class ClusterSproutingModel : public CellSimulationModel {
        public:

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecule::MoleculeDiffusion> const& molecules
        ) override;

        Numerics::Vector3 ComputeForceOnCell(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecule::MoleculeDiffusion> const& moleculeSpaces,
            const CellAlgorithms::CellAlgorithm* pCellAlgorithm
        ) const override;

        void InitializeCells(::std::vector<Cells::Cell>& cells) override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecule::MoleculeDiffusion> const& molecules
        ) override;

        constexpr bool UseCellAlgorithm() const noexcept override;
    };
}

namespace CellSim::Model
{
    constexpr bool ClusterSproutingModel::UseCellAlgorithm() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_MODEL_CLUSTERSPROUTINGMODEL_HPP