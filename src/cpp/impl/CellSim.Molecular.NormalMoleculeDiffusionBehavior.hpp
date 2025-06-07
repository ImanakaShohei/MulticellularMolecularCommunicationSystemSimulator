#ifndef CELLSIM_MOLECULE_NORMALMOLECULEDIFFUSIONBEAVIOR_HPP
#define CELLSIM_MOLECULE_NORMALMOLECULEDIFFUSIONBEAVIOR_HPP

#include "base.hpp"
#include "CellSim.Molecular.MoleculeDiffusionBehavior.hpp"
#include "CellSim.Containers.Span3.hpp"

namespace CellSim::Molecular
{
    class NormalMoleculeDiffusionBehavior : public MoleculeDiffusionBehavior {
        private:

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            Molecular::MoleculeField const& field
        ) override;

        void Diffuse(
            Containers::Span3<double> concentrations,
            Molecular::MoleculeField const& field
        ) override;

        void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            Molecular::MoleculeField const& field
        ) override;
    };
}

#endif //!CELLSIM_MOLECULE_NORMALMOLECULEDIFFUSIONBEAVIOR_HPP