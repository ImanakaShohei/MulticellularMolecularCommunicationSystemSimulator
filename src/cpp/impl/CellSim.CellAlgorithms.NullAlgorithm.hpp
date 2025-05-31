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

        constexpr void BeforeNextStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        constexpr ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& c,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            Cells::Cell const& c,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        constexpr void OnNextStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;
    };
}

namespace CellSim::CellAlgorithms
{
    constexpr void NullAlgorithm::BeforeNextStep(
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Model::Molecule::MoleculeDiffusion> const&
    )
    {
    }

    constexpr ::std::vector<Cells::CellInfo> NullAlgorithm::GetAffectableCellInfos(
        Cells::Cell const&,
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Model::Molecule::MoleculeDiffusion> const&
    )
    {
    }

    inline Threading::Generator<Cells::CellInfo> NullAlgorithm::IterateAffectableCellInfos(
        Cells::Cell const&,
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Model::Molecule::MoleculeDiffusion> const&
    )
    {
        co_return;
    }

    constexpr void NullAlgorithm::OnNextStep(
        ::std::vector<Cells::Cell> const&,
        ::std::vector<Model::Molecule::MoleculeDiffusion> const&
    )
    {
    }
}

#endif //!CELLSIM_CELLALGORITHMS_NULLALGORITHM_HPP