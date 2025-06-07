#ifndef CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIOR_HPP
#define CELLSIM_MOLECULE_MOLECULEDIFFUSIONBEAVIOR_HPP

#include "base.hpp"
#include <vector>

namespace CellSim::Molecular
{
    /// @brief 分子拡散のふるまい
    class MoleculeDiffusionBehavior {
        public:

        /// @brief 種類から作成
        /// @param kind 種類
        /// @return インスタンス
        [[nodiscard]] static MoleculeDiffusionBehavior* FromKind(MoleculeDiffusionBehaviorKind kind);

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