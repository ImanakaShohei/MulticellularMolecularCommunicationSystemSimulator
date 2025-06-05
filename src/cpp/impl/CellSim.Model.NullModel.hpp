#ifndef CELLSIM_MODEL_NULLMODEL_HPP
#define CELLSIM_MODEL_NULLMODEL_HPP

#include "base.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include "CellSim.Numerics.Vector3T.hpp"

namespace CellSim::Model
{
    /// @brief 何もしない力学モデル
    class NullModel : public CellSimulationModel {
        public:

        constexpr void BeforeAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecular::MoleculeDiffusion> const& molecules
        ) override;

        constexpr Numerics::Vector3 ComputeForceOnCell(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeDiffusion> const& moleculeSpaces,
            const CellAlgorithms::CellAlgorithm* pCellAlgorithm
        ) const override;

        constexpr void InitializeCells(::std::vector<Cells::Cell>& cells) override;

        constexpr void OnAdvanceStep(
            ::std::vector<Cells::Cell>& cells,
            ::std::vector<Molecular::MoleculeDiffusion> const& molecules
        ) override;

        constexpr bool UseCellAlgorithm() const noexcept override;
    };
}

namespace CellSim::Model
{
    constexpr void NullModel::BeforeAdvanceStep(
        ::std::vector<Cells::Cell>&,
        ::std::vector<Molecular::MoleculeDiffusion> const&
    )
    {
    }

    constexpr Numerics::Vector3 NullModel::ComputeForceOnCell(
        Cells::Cell const&,
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Molecular::MoleculeDiffusion> const& ,
        const CellAlgorithms::CellAlgorithm*
    ) const
    {
        return Numerics::Vector3();
    }

    constexpr void NullModel::InitializeCells(::std::vector<Cells::Cell>&)
    {
    }

    constexpr void NullModel::OnAdvanceStep(
        ::std::vector<Cells::Cell>&,
        ::std::vector<Molecular::MoleculeDiffusion> const&
    )
    {
    }

    constexpr bool NullModel::UseCellAlgorithm() const noexcept
    {
        return false;
    }
}

#endif //!CELLSIM_MODEL_NULLMODEL_HPP