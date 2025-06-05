#ifndef CELLSIM_MOLECULE_MOLECULEDIFFUSION_HPP
#define CELLSIM_MOLECULE_MOLECULEDIFFUSION_HPP

#include "base.hpp"

#include <vector>

namespace CellSim::Molecular
{
    /// @brief 分子拡散
    class MoleculeDiffusion final {
        private:

        /// @brief ふるまい定義
        MoleculeDiffusionBehavior* m_pBehavior;

        public:

        MoleculeDiffusion(MoleculeDiffusion const&) = delete;

        MoleculeDiffusion& operator=(MoleculeDiffusion const&) = delete;

        void BeforeAdvanceStep(
            ::std::vector<Cells::Cell> const& cells
        );

        void OnAdvanceStep(
            ::std::vector<Cells::Cell> const& cells
        );
    };
}

#endif //!CELLSIM_MOLECULE_MOLECULEDIFFUSION_HPP