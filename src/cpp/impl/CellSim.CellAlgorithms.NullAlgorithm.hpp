#ifndef CELLSIM_CELLALGORITHMS_NULLALGORITHM_HPP
#define CELLSIM_CELLALGORITHMS_NULLALGORITHM_HPP

#include "base.hpp"
#include "CellSim.Cells.Cell.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"
#include "CellSim.Threading.Generator.hpp"

namespace CellSim::CellAlgorithms
{
    /// @brief 何もしないアルゴリズム
    class NullAlgorithm : public CellAlgorithm {
        public:

        constexpr void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) override;

        ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) const override;

        Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) const override;

        constexpr void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Molecular::MoleculeField> const& molecules
        ) override;
    };
}

namespace CellSim::CellAlgorithms
{
    constexpr void NullAlgorithm::BeforeAdvanceStep(
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Molecular::MoleculeField> const&
    )
    {
    }

    inline ::std::vector<Cells::CellInfo> NullAlgorithm::GetAffectableCellInfos(
        Cells::Cell const&,
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Molecular::MoleculeField> const&
    ) const
    {
        return {};
    }

    inline Threading::Generator<Cells::CellInfo> NullAlgorithm::IterateAffectableCellInfos(
        Cells::Cell const&,
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Molecular::MoleculeField> const&
    ) const
    {
        co_return;
    }

    constexpr void NullAlgorithm::OnAdvanceStep(
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Molecular::MoleculeField> const&
    )
    {
    }
}

#endif //!CELLSIM_CELLALGORITHMS_NULLALGORITHM_HPP