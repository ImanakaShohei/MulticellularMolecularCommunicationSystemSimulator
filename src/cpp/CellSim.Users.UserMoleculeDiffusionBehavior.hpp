#ifndef CELLSIM_USERS_USERMOLECULEDIFFUSIONBEAVIOR_HPP
#define CELLSIM_USERS_USERMOLECULEDIFFUSIONBEAVIOR_HPP

#include "impl/base.hpp"
#include "impl/CellSim.Molecular.MoleculeDiffusionBehavior.hpp"

namespace CellSim::Users
{
    class UserMoleculeDiffusionBehavior : public Molecular::MoleculeDiffusionBehavior {
        private:

        // TODO: ここにメンバーを追加します

        public:

        UserMoleculeDiffusionBehavior();
        ~UserMoleculeDiffusionBehavior();

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

#endif //!CELLSIM_USERS_USERMOLECULEDIFFUSIONBEAVIOR_HPP