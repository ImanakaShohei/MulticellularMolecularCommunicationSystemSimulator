#ifndef CELLSIM_MODEL_CELLGROWTHMODEL_HPP
#define CELLSIM_MODEL_CELLGROWTHMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"

namespace CellSim::Model
{
    class CellGrowthModel : public CellSimulationModel {
        public:

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) override;

        Numerics::Vector3 ComputeForceOnCell(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& moleculeSpaces,
            const CellAlgorithms::CellAlgorithm* pCellAlgorithm
        ) const override;

        void InitializeCells(::std::vector<Cells::Cell>& cells) override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) override;

        constexpr bool UseCellAlgorithm() const noexcept override;
    };
}

namespace CellSim::Model
{
    constexpr bool CellGrowthModel::UseCellAlgorithm() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_MODEL_CELLGROWTHMODEL_HPP