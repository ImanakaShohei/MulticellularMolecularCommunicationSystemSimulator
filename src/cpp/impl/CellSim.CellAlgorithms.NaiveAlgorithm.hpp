#ifndef CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP
#define CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim::CellAlgorithms
{
    class NaiveAlgorithm : public CellAlgorithm {
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

        constexpr bool HasMultithreadingSupport() const noexcept override;

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
    constexpr void NaiveAlgorithm::BeforeAdvanceStep(
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Molecular::MoleculeField> const&
    )
    {
    }

    constexpr bool NaiveAlgorithm::HasMultithreadingSupport() const noexcept
    {
        return true;
    }

    constexpr void NaiveAlgorithm::OnAdvanceStep(
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Molecular::MoleculeField> const&
    )
    {
    }
}

#endif //!CELLSIM_CELLALGORITHMS_NAIVEALGORITHM_HPP