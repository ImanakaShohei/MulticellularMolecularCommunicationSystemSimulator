#ifndef CELLSIM_CELLALGORITHMS_CELLLIST_HPP
#define CELLSIM_CELLALGORITHMS_CELLLIST_HPP

#include "base.hpp"
#include "CellSim.CellAlgorithms.CellAlgorithm.hpp"

namespace CellSim::CellAlgorithms
{
    /// @brief Cell-List
    class CellList : public CellAlgorithm {
        private:



        public:
        
        CellList();
        ~CellList();

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        ::std::vector<Cells::CellInfo> GetAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        Threading::Generator<Cells::CellInfo> IterateAffectableCellInfos(
            Cells::Cell const& target,
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            ::std::vector<Model::Molecule::MoleculeDiffusion> const& molecules
        ) override;
    };
}

#endif //!CELLSIM_CELLALGORITHMS_CELLLIST_HPP