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

        Cells::CellGrowthResult ComputeGrowth(Cells::Cell const& cell) override;
        double ComputeMoleculeEmitAmount(Cells::Cell const& cell, Molecular::MoleculeField const& field) override;
        CellBehavior* CreateClone() const override;
        
        bool HasState() const noexcept override;
    };
}

#endif //!CELLSIM_USERS_USERCELLBEHAVIOR_HPP