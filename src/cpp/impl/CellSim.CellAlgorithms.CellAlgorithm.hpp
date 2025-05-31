#ifndef CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP
#define CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP

#include "base.hpp"
#include <vector>

namespace CellSim::CellAlgorithms
{
    /// @brief 高速化アルゴリズム
    class CellAlgorithm {
        public:

        constexpr virtual ~CellAlgorithm() {}

        virtual void BeforeNextStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) = 0;

        virtual ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& c,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) = 0;

        virtual Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            Cells::Cell const& c,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) = 0;

        virtual void OnNextStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) = 0;
        
    };
}

#endif //!CELLSIM_CELLALGORITHMS_CELLALGORITHM_HPP