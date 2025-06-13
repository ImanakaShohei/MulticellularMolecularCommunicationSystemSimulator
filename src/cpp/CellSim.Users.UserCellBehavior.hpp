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

        Cells::CellDivisionResult ComputeDivisionOutcome(const Cells::Cell* sender) override;
        Cells::CellGrowthResult ComputeGrowth(const Cells::Cell* sender) override;
        
        double ComputeMetabolicChange(const Cells::Cell* sender, Cells::CellMetabolicArgs args) override;
        double ComputeMoleculeEmitAmount(const Cells::Cell* sender, Cells::CellMoleculeEmissionArgs args) override;
        
        CellBehavior* CreateClone() const override;
        
        bool HasState() const noexcept override;

        Numerics::Vector3 OnSenseMolecules(const Cells::Cell* sender, Cells::CellMoleculeSensingArgs args) override;

        bool ShouldDivideThisStep(const Cells::Cell* sender) noexcept override;
    };
}

#endif //!CELLSIM_USERS_USERCELLBEHAVIOR_HPP