#ifndef CELLSIM_USERS_USERCELLBEHAVIOR_HPP
#define CELLSIM_USERS_USERCELLBEHAVIOR_HPP

#include "impl/base.hpp"
#include "impl/CellSim.Cells.CellBehavior.hpp"

namespace CellSim::Users
{
    /// @brief ユーザー定義の細胞のふるまい
    class UserCellBehavior : public Cells::CellBehavior {
        public:

        UserCellBehavior() = default;

        CellDivisionResult ComputeDivisionOutcome(const Cells::Cell* sender) override;
        Cells::CellGrowthResult ComputeGrowth(Cells::Cell const& cell) override;
        
        double ComputeMetabolicChange(const Cells::Cell* sender, Molecular::MoleculeInfo args) override;
        double ComputeMoleculeEmitAmount(Cells::Cell const& cell, Molecular::MoleculeField const& field) override;
        
        CellBehavior* CreateClone() const override;
        
        bool HasState() const noexcept override;

        bool ShouldDivideThisStep() noexcept override;
    };
}

#endif //!CELLSIM_USERS_USERCELLBEHAVIOR_HPP