#ifndef CELLSIM_MODEL_MOLECULE_MOLECULEDIFFUSION_HPP
#define CELLSIM_MODEL_MOLECULE_MOLECULEDIFFUSION_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::Model::Molecule
{
    /// @brief 分子拡散モデル
    class MoleculeDiffusion final {
        public:

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells
        );

        void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells
        );
    };
}

#endif //!CELLSIM_MODEL_MOLECULE_MOLECULEDIFFUSION_HPP