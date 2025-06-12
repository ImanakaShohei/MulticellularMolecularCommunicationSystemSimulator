#ifndef CELLSIM_USERS_USERMOLECULEBEAVIOR_HPP
#define CELLSIM_USERS_USERMOLECULEBEAVIOR_HPP

#include "impl/base.hpp"
#include "impl/CellSim.Molecular.MoleculeBehavior.hpp"

namespace CellSim::Users
{
    class UserMoleculeBehavior : public Molecular::MoleculeBehavior {
        private:

        // TODO: ここにメンバーを追加します

        public:

        UserMoleculeBehavior();
        UserMoleculeBehavior(Molecular::BoundaryCondition boundaryCondition);
        ~UserMoleculeBehavior();

        void BeforeAdvanceStep(
            const Molecular::MoleculeField* sender,
            Molecular::MoleculeBehaviorStepArgs args
        ) override;

        void Diffuse(
            const Molecular::MoleculeField* sender,
            Molecular::MoleculeDiffusionArgs args
        ) override;

        void InitializeMolecules(
            const Molecular::MoleculeField* sender,
            Molecular::MoleculeInitializationArgs args
        ) override;

        void OnAdvanceStep(
            const Molecular::MoleculeField* sender,
            Molecular::MoleculeBehaviorStepArgs args
        ) override;
    };
}

#endif //!CELLSIM_USERS_USERMOLECULEBEAVIOR_HPP