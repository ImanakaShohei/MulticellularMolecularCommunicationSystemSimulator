#ifndef CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIOR_HPP
#define CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIOR_HPP

#include "base.hpp"
#include <vector>

namespace CellSim::Molecular
{
    /// @brief 分子拡散のふるまい
    class MoleculeDiffusionBehavior {
        private:

        public:

        virtual void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            MoleculeField const& field
        ) = 0;

        virtual void Diffuse(
            Containers::Span3<double> concentrations,
            MoleculeField const& field
        ) = 0;

        virtual void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells,
            MoleculeField const& field
        ) = 0;
    };
}

#endif //!CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIOR_HPP